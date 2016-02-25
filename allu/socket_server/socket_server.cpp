#include <string>
#include <vector>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <map>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <assert.h>
#include "socket_utilities.hpp"
#include "msg.hpp"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::thread;
using std::vector;

void thread_fn(void *srv, int fd);

class sock_server
{
    public:
        explicit sock_server(string addr)
        {
            m_addr = addr;
        }
        ~sock_server()
        {
        }
        bool start()
        {
            m_sock = init_server_sock(m_addr);
            if (m_sock == -1)
            {
                cout << "cannot create socket\n";
                return false;
            }
            m_stop = false;
            run();
        }
        bool stop()
        {
            m_stop = true;
            destroy_sock(m_addr);
        }
        void run()
        {
            while (m_stop == false)
            {
                bool err;
                if (ready_to_read(m_sock, 1000, &err))
                {
                    int new_conn_fd = accept_sock_conn(m_sock);
                    auto new_conn = new thread(thread_fn, this, new_conn_fd);
                    m_threads.push_back(new_conn);
                }
            }
        }
        void get_user_info(map<string, string> *out)
        {
            *out = m_users;
        }
        void set_user_info(string user, string passwd)
        {
            m_users[user] = passwd;
        }
        void conn_handler(int conn_sock, const map<string, string> *users)
        {
            // just in case
            char *buffer = new char [1024];
            bool valid_user = false;

            do
            {
                int read_bytes = read_fd(conn_sock, buffer, sizeof(msg_hdr), 1000);
                // Client did not send anything
                if (read_bytes == 0)
                {
                    continue;
                }
                assert(read_bytes == sizeof(msg_hdr));
                msg_hdr *hdr;
                hdr = reinterpret_cast<msg_hdr *>(buffer);
                if (hdr->type == CONN_REQ)
                {
                    cout << "Conn REQ\n";
                    // Check if user/password
                    read_bytes += read_fd(conn_sock, &buffer[sizeof(msg_hdr)],
                                          hdr->len - sizeof(msg_hdr), 100);
                    // FIXME: retry
                    assert(read_bytes == sizeof(conn_req_msg));
                    conn_req_msg *req_msg;
                    req_msg = reinterpret_cast<conn_req_msg *>(buffer);
                    string new_user(req_msg->name);
                    string passwd(req_msg->passwd);
                    // FIXME - use C++11 to get iterator and check passwd
                    auto user_iter = users->find(new_user);
                    if (user_iter == users->end())
                    {
                        // Abort this connection
                        cout << "User " << new_user << " has invalid passwd\n";
                        break;
                    }
                    valid_user = true;
                    cout << "User " << new_user << " is valid\n";
                    // Write connection succeed
                    conn_succeed_msg succeed_msg;
                    succeed_msg.hdr.type = CONN_SUCCEED;
                    succeed_msg.hdr.len = sizeof(succeed_msg);
                    int written = write_fd(conn_sock, reinterpret_cast<char *>(&succeed_msg),
                                           sizeof(succeed_msg), 1000);
                    if (written != sizeof(succeed_msg))
                    {
                        // FIXME - retry?
                        cout << "Cannot send conn succeed\n";
                    }
                }
                else if (hdr->type == CLIENT_TS)
                {
                    cout << "Client TS\n";
                    read_bytes += read_fd(conn_sock, &buffer[sizeof(msg_hdr)],
                                          hdr->len - sizeof(msg_hdr), 100);
                    assert(read_bytes == sizeof(client_ts_msg));
                    if (!valid_user)
                    {
                        // Ignore it. User should send connect request
                        // first. We could either terminate connection
                        // or ignore it.
                        continue;
                    }
                    // Send ACK
                    server_ack_msg ack_msg;
                    ack_msg.hdr.type = SRV_ACK;
                    ack_msg.hdr.len = sizeof(ack_msg);
                    int written = write_fd(conn_sock,
                                           reinterpret_cast<char *>(&ack_msg),
                                           sizeof(ack_msg), 100);
                    if (written != sizeof(ack_msg))
                    {
                        cout << "Cannot send ACK\n";
                        break;
                    }
                }
                else
                {
                    cout << "unknows msg type " << hdr->type << endl;
                    break;
                }
            }
            while(true);

            delete [] buffer;
        }
    private:
        string m_addr;
        int m_sock;
        bool m_stop;
        map<string, string> m_users;
        vector<thread *> m_threads;
};

void thread_fn(void *ctxt, int fd)
{
    auto srv = reinterpret_cast<sock_server *>(ctxt);
    map<string, string> user_info;
    srv->get_user_info(&user_info);
    srv->conn_handler(fd, &user_info);
}

int main()
{
    sock_server srv("test_socket");
    srv.set_user_info("test_user1", "passwd");
    srv.start();
    return 0;
}
