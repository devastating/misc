#include "socket_utilities.hpp"
#include "msg.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
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

static bool g_running = false;

uint64_t get_ts_ns()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    uint64_t ret = (tv.tv_sec * 1000000 + tv.tv_usec);
    return ret * 1000;
}

static void ack_recv_thread_fn(void *ctxt, bool *acked);

void client_fn(void *ctxt);

class socket_client
{
    public:
        socket_client(bool is_tcp)
        {
            m_tcp = is_tcp;
            m_fd = -1;
            m_thread = nullptr;
        }
        bool start(string server_addr, string user, string passwd)
        {
            struct sockaddr_un addr;

            unique_lock<mutex> lck(m_mtx);
            
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

            m_user = user;
            m_passwd = passwd;
            m_thread = new thread(client_fn, this);
            m_stop = false;
            cout << "Client " << m_user << " started\n";
            return true;
        }

        void run()
        {
            // First send conn req
            bool err;
            if (ready_to_write(m_fd, 1000, &err))
            {
                conn_req_msg req_msg;
                req_msg.hdr.type = CONN_REQ;
                req_msg.hdr.len = sizeof(req_msg);
                strncpy(req_msg.name, m_user.c_str(), sizeof(req_msg.name));
                strncpy(req_msg.passwd, m_passwd.c_str(), sizeof(req_msg.passwd));
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
                    cout << "ERROR: User not allowed\n";
                    m_stop = true;
                }
            }

            while(m_stop == false)
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
                    while (retry <= 5)
                    {
                        int written = write_fd(m_fd, reinterpret_cast<char *>(&client_ts), sizeof(client_ts), 1000);
                        if (written != sizeof(client_ts))
                        {
                            // Cannot write whole msg. for now
                            cout << "ERROR: send TS to server\n";
                        }
                        auto ack_thread = thread(ack_recv_thread_fn, this,
                                                 &acked);
                        unique_lock<mutex> lck(m_ack_mtx);
                        // Wait for 7 seconds at most
                        m_cv.wait_for(lck, std::chrono::seconds(7));
                        ack_thread.join();
                        if (acked)
                        {
                            cout << "INFO: Server acked\n";
                            break;
                        }
                        retry++;
                    }
                    if (acked == false)
                    {
                        // Server did not respond after 5 retry
                        cout << "ERROR: server does not respond after 5 retries\n";
                        break;
                    }
                }
            }
        }

        void stop()
        {
            unique_lock<mutex> lck(m_mtx);
            if (m_fd == -1)
            {
                return;
            }
            m_stop = true;
            lck.unlock();
            m_thread->join();
            m_thread = nullptr;
            m_fd = -1;
            cout << "Client " << m_user << " stopped\n";
        }

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
        bool m_stop;
        string m_addr;
        mutex m_mtx;
        mutex m_ack_mtx;
        condition_variable m_cv;
        thread *m_thread;
        string m_user;
        string m_passwd;
};

void client_fn(void *ctxt)
{
    auto sock_cli = reinterpret_cast<socket_client *>(ctxt);
    sock_cli->run();
}

void ack_recv_thread_fn(void *ctxt, bool *acked)
{
    auto sock_cli = reinterpret_cast<socket_client *>(ctxt);
    sock_cli->ack_recv_thread(acked);
}

void sig_handler(int signum)
{
    g_running = false;
}

int main()
{
    signal(SIGINT, sig_handler);
    socket_client client(true);
    if (client.start("test_socket", "test_user1", "passwd"))
    {
        g_running = true;
        while (g_running)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        client.stop();
    }
    return 0;
}
