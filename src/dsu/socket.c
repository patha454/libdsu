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

#include "dsu/socket.h"
#include "dsu/packet.h"
#include "dsu/status.h"
#include <poll.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/**
 * \brief Maximum number of pending DSU requests to support.
 */
#define DSU_REQUEST_BACKLOG 4

/**
 * Get the name (file path) of the Unix domain socket used by the host
 * process.
 *
 * \param name Memory to copy the socket name into.
 * \param length Length of `name`.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
static DsuStatus
dsuGetServerSocketName(char* name, size_t length)
{
  char* homeDir = getenv("HOME");
  if (homeDir == NULL) {
    return DSU_PANIC;
  }
  snprintf(name, length, "%s/%d_dsu", homeDir, getpid());
  return DSU_SUCCESS;
}

DsuStatus
dsuInitServerSocket(struct DsuServerSocket* dsuSocket)
{
  DsuStatus status = DSU_SUCCESS;
  dsuSocket->fileDescriptor = socket(AF_UNIX, SOCK_STREAM, 0);
  if (dsuSocket->fileDescriptor == -1) {
    return DSU_ERROR_OPEN_SOCKET;
  }
  status = dsuGetServerSocketName(dsuSocket->filePath, DSU_SOCKET_PATH_LEN);
  if (status != DSU_SUCCESS) {
    return status;
  }
  struct sockaddr_un address;
  address.sun_family = AF_UNIX;
  strncpy(address.sun_path, dsuSocket->filePath, DSU_SOCKET_PATH_LEN);
  if (bind(dsuSocket->fileDescriptor,
           (struct sockaddr*)&address,
           sizeof address) == -1) {
    return DSU_ERROR_OPEN_SOCKET;
  }
  if (listen(dsuSocket->fileDescriptor, DSU_REQUEST_BACKLOG) == -1) {
    return DSU_ERROR_OPEN_SOCKET;
  }
  return DSU_SUCCESS;
}

DsuStatus
dsuInitClientSocket(struct DsuSocket* dsuSocket, char* socketPath)
{
  dsuSocket->fileDescriptor = socket(AF_UNIX, SOCK_STREAM, 0);
  if (dsuSocket->fileDescriptor == -1) {
    return DSU_ERROR_OPEN_SOCKET;
  }
  struct sockaddr_un address;
  address.sun_family = AF_UNIX;
  strncpy(address.sun_path, socketPath, DSU_SOCKET_PATH_LEN);
  if (connect(dsuSocket->fileDescriptor,
              (struct sockaddr*)&address,
              sizeof address) == -1) {
    return DSU_ERROR_CONNECT_SOCKET;
  }
  return DSU_SUCCESS;
}

DsuStatus
dsuDestroyServerSocket(struct DsuServerSocket* dsuSocket)
{
  if (shutdown(dsuSocket->fileDescriptor, SHUT_RD) == -1) {
    return DSU_ERROR_CLOSE_SOCKET;
  }
  if (close(dsuSocket->fileDescriptor) == -1) {
    return DSU_ERROR_CLOSE_SOCKET;
  }
  if (unlink(dsuSocket->filePath) == -1) {
    return DSU_ERROR_CLOSE_SOCKET;
  }
  return DSU_SUCCESS;
}

bool
dsuServerConnectionPending(struct DsuServerSocket* dsuSocket)
{
  struct pollfd pollfd;
  pollfd.fd = dsuSocket->fileDescriptor;
  pollfd.events = POLLIN;
  int pollStatus = poll(&pollfd, 1, 0);
  if (pollStatus == -1) {
    return false;
  }
  if (pollStatus == 0) {
    return false;
  }
  return true;
}

DsuStatus
dsuServerAcceptConnection(struct DsuServerSocket* serverSocket,
                          struct DsuSocket* clientSocket)
{
  struct sockaddr_un address;
  socklen_t addressLength = sizeof address;
  clientSocket->fileDescriptor = accept(
    serverSocket->fileDescriptor, (struct sockaddr*)&address, &addressLength);
  if (clientSocket->fileDescriptor == -1) {
    return DSU_ERROR_OPEN_SOCKET;
  }
  strncpy(clientSocket->filePath, address.sun_path, DSU_SOCKET_PATH_LEN);
  return DSU_SUCCESS;
}

DsuStatus
dsuSocketReadPacket(struct DsuSocket* socket, uint8_t* buffer, size_t bufferLen)
{
  if (bufferLen < sizeof(struct DsuPacketHeader)) {
    return DSU_BUFFER_OVERUN;
  }
  size_t bytesRead = 0;
  bytesRead =
    read(socket->fileDescriptor, buffer, sizeof(struct DsuPacketHeader));
  if (bytesRead != ((struct DsuPacketHeader*)buffer)->length) {
    return DSU_BAD_READ;
  }
  size_t bytesRemaining =
    ((struct DsuPacketHeader*)buffer)->length - sizeof(struct DsuPacketHeader);
  if (bufferLen < bytesRemaining + bytesRead) {
    return DSU_BUFFER_OVERUN;
  }
  bytesRead = read(socket->fileDescriptor,
                   buffer + sizeof(struct DsuPacketHeader),
                   bytesRemaining);
  if (bytesRead != bytesRemaining) {
    return DSU_BAD_READ;
  }
  return DSU_SUCCESS;
}

DsuStatus
dsuSocketWritePacket(struct DsuSocket* socket, struct DsuPacketHeader* packet)
{
  ssize_t written =
    write(socket->fileDescriptor, (void*)packet, packet->length);
  if (written == -1 || (size_t)written != packet->length) {
    return DSU_BAD_WRITE;
  }
  return DSU_SUCCESS;
}
