#include "socket_utilities.hpp"
#include "msg.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <condition_variable>

using std::string;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::cout;
using std::endl;
using std::condition_variable;

uint64_t get_ts_ns()
{
    return 100;
}

static void ack_recv_thread_fn(void *ctxt, bool *acked);

class socket_client
{
    public:
        socket_client(bool is_tcp)
        {
            m_tcp = is_tcp;
        }
        bool start(string server_addr, string user, string passwd)
        {
            struct sockaddr_un addr;

            // FIXME - tcp/udp support
            m_fd = socket(AF_UNIX, SOCK_STREAM, 0);
            if (m_fd == -1)
            {
                return false;
            }

            memset(&addr, 0, sizeof(addr));
            addr.sun_family = AF_UNIX;
            strncpy(addr.sun_path,
                    server_addr.c_str(),
                    sizeof(addr.sun_path) - 1);

            if (connect(m_fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1)
            {
                close(m_fd);
                m_fd = -1;
                return false;
            }

            // First send conn req
            bool err;
            if (ready_to_write(m_fd, 1000, &err))
            {
                conn_req_msg req_msg;
                req_msg.hdr.type = CONN_REQ;
                req_msg.hdr.len = sizeof(req_msg);
                strncpy(req_msg.name, user.c_str(), sizeof(req_msg.name));
                strncpy(req_msg.passwd, passwd.c_str(), sizeof(req_msg.passwd));
                int written = write_fd(m_fd, reinterpret_cast<char *>(&req_msg), sizeof(req_msg), 1000);
                if (written != sizeof(req_msg))
                {
                    cout << "WARN: cannot send out conn req\n";
                    cout << "written " << written << endl;
                }

                msg_hdr lcl_hdr;
                int read_bytes = read_fd(m_fd, reinterpret_cast<char *>(&lcl_hdr), sizeof(lcl_hdr), 1000);
                if (read_bytes != sizeof(lcl_hdr))
                {
                    cout << "WARN: cannot read conn resp\n";
                }
                if (lcl_hdr.type != CONN_SUCCEED)
                {
                    // We are not allowed to connect..
                    cout << "User not allowed\n";
                    return false;
                }
            }

            while(true)
            {
                if (ready_to_write(m_fd, 1000, &err))
                {
                    client_ts_msg client_ts;
                    client_ts.hdr.type = CLIENT_TS;
                    client_ts.hdr.len= sizeof(client_ts);
                    auto ts_now = get_ts_ns();
                    client_ts.ts_msb = ts_now >> 32;
                    client_ts.ts_lsb = ts_now & 0xffffffff;
                    int retry = 0;
                    bool acked = false;
                    while (retry < 5)
                    {
                        auto ack_thread = thread(ack_recv_thread_fn, this,
                                                 &acked);
                        unique_lock<mutex> lck(m_mtx);
                        // Wait for 7 seconds at most
                        m_cv.wait_for(lck, std::chrono::seconds(7));
                        ack_thread.join();
                        if (acked)
                        {
                            break;
                        }
                        retry++;
                    }
                    if (acked == false)
                    {
                        // Server did not respond after 5 retry
                        break;
                    }
                }
            }
        }

        bool stop();
        void ack_recv_thread(bool *acked)
        {
            // To read ACK in 2 second
            msg_hdr hdr;
            int read_bytes = read_fd(m_fd, reinterpret_cast<char *>(&hdr), sizeof(hdr), 2000);
            if (read_bytes == sizeof(hdr))
            {
                *acked = true;
            }
            else
            {
                *acked = false;
                m_cv.notify_one();
            }
        }
    private:
        int m_fd;
        bool m_tcp;
        string m_addr;
        mutex m_mtx;
        condition_variable m_cv;
};

void ack_recv_thread_fn(void *ctxt, bool *acked)
{
    auto sock_cli = reinterpret_cast<socket_client *>(ctxt);
    sock_cli->ack_recv_thread(acked);
}

int main()
{
    socket_client client(true);
    client.start("test_socket", "test_user1", "passwd");
    return 0;
}
