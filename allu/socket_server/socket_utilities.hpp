#include <errno.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <assert.h>

int init_server_sock(std::string address);
int accept_sock_conn(int fd);
int destroy_sock(std::string name);
bool poll_events(int fd, unsigned char event, int block_ms, bool *error);
bool ready_to_read(int fd, int block_ms, bool *error);
bool ready_to_write(int fd, int block_ms, bool *error);
int read_fd(int fd, char *read_buf, size_t len,
            int ms_to_try);
int write_fd(int fd, const char *write_buf,
             size_t len, int ms_to_try);
