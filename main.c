#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

struct DsuServer
{
    int socketFd,
    char[32] socketName,
};

void DsuInitServer(struct DsuServer* server)
{
    int socketFd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socketFd == -1) {
        perror("Create server socket: ");
        exit(EXIT_FAILURE);
    }
    char name[108];
    sprintf(name, "%d_dsu", getpid());
    printf("%s\n", name);
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, name);
    int status = bind(socketFd, (struct sockaddr*) &address, sizeof address);
    if (status == -1) {
        perror("Bind server socket: ");
        exit(EXIT_FAILURE);
    }
    status = listen(socketFd, 1);
    if (status == -1) {
        perror("Listen to server socket: ");
        exit(EXIT_FAILURE);
    }
    shutdown(socketFd, SHUT_RDWR);
    close(socketFd);
    unlink(name);
}

int
main(int argc, char** argv)
{
  struct DsuServer server;
  DsuInitServer(&server);
  return EXIT_SUCCESS;
}