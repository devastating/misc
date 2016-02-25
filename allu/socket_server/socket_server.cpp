#include <string>
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

using std::string;
using std::cout;
using std::endl;
using std::map;

enum msg_types
{
    CONN_REQ = 0,
    CLIENT_TS,
    SRV_ACK
};

struct msg_hdr
{
    long type;
    long len;
};

struct conn_req_msg
{
    struct msg_hdr hdr;
    char name[256];
    char passwd[256];
};

struct client_ts_msg
{
    struct msg_hdr hdr;
    long ts_msb;
    long ts_lsb;
};

struct server_ack_msg
{
    struct msg_hdr hdr;
};

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
                    cout << "new connection fd " << new_conn_fd << endl;
                    close(new_conn_fd);
                }
                else
                {
                    cout << "No conn..\n";
                }
            }
        }
        void conn_thread_fn(int conn_sock, const map<string, string> *users)
        {
            // just in case
            char *buffer = new char [1024];
            bool valid_user = false;

            do
            {
                int read_bytes = read_fd(conn_sock, buffer, sizeof(msg_hdr), 100);
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
                    //if (users[new_user] != passwd)
                    {
                        // Abort this connection
                        cout << "User " << new_user << " has invalid passwd\n";
                        break;
                    }
                    valid_user = true;
                }
                else if (hdr->type == CLIENT_TS)
                {
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
};


int main()
{
    sock_server srv("test_socket");
    srv.start();
    return 0;
}
