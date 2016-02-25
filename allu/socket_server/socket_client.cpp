#include "socket_utilities.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

using std::string;

class socket_client
{
    public:
        socket_client(bool is_tcp);
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
        }

        bool stop();
    private:
        int m_fd;
        bool m_tcp;
        string m_addr;
};

int main()
{
    return 0;
}
