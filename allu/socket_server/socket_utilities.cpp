#include "socket_utilities.hpp"

using std::string;

int init_server_sock(string address)
{
    struct sockaddr_un sock_addr;
    int fd;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
    {
        //perror("socket error");
        return (-1);
    }

    // Try to clean up stale socket address first
    unlink(address.c_str());

    // Bind & Listen
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sun_family = AF_UNIX;
    strncpy(sock_addr.sun_path, address.c_str(), sizeof(sock_addr.sun_path) - 1);
    if (bind(fd, reinterpret_cast<struct sockaddr *>(&sock_addr), sizeof(sock_addr)) == -1)
    {
        //perror("bind error");
        return (-1);
    }
    if (listen(fd, 5) == -1)
    {
        //perror("listen error");
        return (-1);
    }

    return fd;
}

int accept_sock_conn(int fd)
{
    return accept(fd, NULL, NULL);
}

int destroy_sock(string name)
{
    return unlink(name.c_str());
}

bool poll_events(int fd, unsigned char event, int block_ms, bool *error)
{
    bool ready = false;
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = event;

    *error = false;
    if (poll(&pfd, 1, block_ms) != 0)
    {
        if (pfd.revents & event)
        {
            ready = true;
        }

        if (pfd.revents & (POLLERR | POLLHUP))
        {
            *error = true;
        }
    }
    return ready;
}

bool ready_to_read(int fd, int block_ms, bool *error)
{
    return poll_events(fd, POLLIN, block_ms, error);
}

bool ready_to_write(int fd, int block_ms, bool *error)
{
    return poll_events(fd, POLLOUT, block_ms, error);
}

int read_fd(int fd, char *read_buf, size_t len,
            int ms_to_try)
{
    size_t read_bytes = 0;
    const int min_poll_ms = 50;
    bool error;

    if (ms_to_try == 0)
    {
        // read immediately - succeed or failed immediately
        read_bytes = read(fd, &read_buf[0], len);
    }
    else
    {
        while (read_bytes < len)
        {
            bool ready = ready_to_read(fd, min_poll_ms, &error);

            if (error)
            {
                // Got an error in socket
                break;
            }
            if (ready)
            {
                int rc = read(fd, &read_buf[read_bytes], len - read_bytes);
                if (rc > 0)
                {
                    read_bytes += rc;
                }
                else
                {
                    // Got an error
                    break;
                }
            }

            ms_to_try -= min_poll_ms;
            if (ms_to_try <= 0)
            {
                break;
            }
        }
    }
    return read_bytes;
}

int write_fd(int fd, const char *write_buf,
             size_t len, int ms_to_try)
{
    size_t written_bytes = 0;
    const int min_poll_ms = 50;
    bool error;

    while (written_bytes < len)
    {
        bool ready = ready_to_write(fd, min_poll_ms, &error);

        if (error)
        {
            // Got an error in socket
            break;
        }
        if (ready)
        {
            int rc = write(fd, &write_buf[written_bytes], len - written_bytes);
            if (rc > 0)
            {
                written_bytes += rc;
            }
            else
            {
                // Got an error
                break;
            }
        }

        if (ms_to_try)
        {
            ms_to_try -= min_poll_ms;
            if (ms_to_try <= 0)
            {
                break;
            }
        }
    }
    return written_bytes;
}
