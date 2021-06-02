#include <dsuStatus.h>

#ifndef DSU_SOCKET_H_
#define DSU_SOCKET_H_

struct DsuServerSocket
{
    int fileDescriptor;
    char* filePath;
};

DsuStatus dsuInitServerSocket(struct DsuServerSocket* dsuSocket);
DsuStatus dsuDestroyServerSocket(struct DsuServerSocket* dsuSocket);
#endif
