/**
 * \file dsuSocket.c
 * \brief `dsuSocket.c` provides implements UNIX domain socket communication
 * with a DSU service.
 * 
 * \see `dsuSocket.h` for detailed documentation comments.
 * 
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>.
 * \copyright BSL-1.0.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "dsu/socket.h"
#include "dsu/status.h"

/**
 * \brief Maximum length used for socket path names.
 *
 * The length (108) bytes is not arbitrary. It is the maximum length allowed by
 * the `struct sockaddr_un`.
 */
#define DSU_SOCKET_PATH_LEN 108

/**
 * \brief Maximum number of pending DSU requests to support.
 */
#define DSU_REQUEST_BACKLOG 4

static DsuStatus dsuGetServerSocketName(char* name, size_t length) {
    char* homeDir = getenv("HOME");
    if (homeDir == NULL) {
        return DSU_PANIC;
    }
    snprintf(name, length, "%s/%d_dsu", homeDir, getpid());
    return DSU_SUCCESS;
}

DsuStatus dsuInitServerSocket(struct DsuServerSocket* dsuSocket)
{
    DsuStatus status = DSU_SUCCESS;
    dsuSocket->fileDescriptor = socket(AF_UNIX, SOCK_STREAM, 0);
    if (dsuSocket->fileDescriptor == -1) {
        return DSU_ERROR_SOCKET;
    }
    dsuSocket->filePath = malloc(DSU_SOCKET_PATH_LEN);
    if (dsuSocket->filePath == NULL) {
        return DSU_ERROR_MEMORY;
    }
    status = dsuGetServerSocketName(dsuSocket->filePath, DSU_SOCKET_PATH_LEN);
    if (status != DSU_SUCCESS) {
        return status;
    }
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, dsuSocket->filePath, DSU_SOCKET_PATH_LEN);
    if (bind(dsuSocket->fileDescriptor, (struct sockaddr*) &address, sizeof address) == -1)
    {
        return DSU_ERROR_SOCKET;
    }
    if (listen(dsuSocket->fileDescriptor, DSU_REQUEST_BACKLOG) == -1)
    {
        return DSU_ERROR_SOCKET;
    }
    return DSU_SUCCESS;
}

/**
 * \brief Close the DSU server's Unix socket, and remove the file system entry. 
 *
 * \param dsuSocket Pointer to the socket to close.
 * \return `DSU_SUCCESS` or an error on failure.
 */
DsuStatus dsuDestroyServerSocket(struct DsuServerSocket* dsuSocket)
{
    if (shutdown(dsuSocket->fileDescriptor, SHUT_RD) == -1) {
        return DSU_ERROR_SOCKET;
    }
    if (close(dsuSocket->fileDescriptor) == -1) {
        return DSU_ERROR_SOCKET;
    }
    if (unlink(dsuSocket->filePath) == -1) {
        return DSU_ERROR_SOCKET;
    }
    return DSU_SUCCESS;
}