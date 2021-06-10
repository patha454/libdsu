/**
 * \file socket.h
 * \brief `dsu/socket.h` provides an interface for creating and using sockets to
 * communicate with the DSU service.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>.
 * \copyright BSL-1.0.
 */

#ifndef DSU_SOCKET_H_
#define DSU_SOCKET_H_

#include "dsu/status.h"
#include "packet/packet.h"
#include "stdint.h"
#include <stdbool.h>

/**
 * \brief Maximum length used for socket path names.
 *
 * The length (108) bytes is not arbitrary. It is the maximum length allowed by
 * the `struct sockaddr_un`.
 */
#define DSU_SOCKET_PATH_LEN 108

struct DsuServerSocket
{
  int fileDescriptor;
  char filePath[DSU_SOCKET_PATH_LEN];
};

struct DsuSocket
{
  int fileDescriptor;
  char filePath[DSU_SOCKET_PATH_LEN];
};

/**
 * \brief Create and open a new Unix domain server socket to listen for DSU
 * requests.
 *
 * \param dsuSocket Memory to return the new socket in.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus
dsuInitServerSocket(struct DsuServerSocket* dsuSocket);

/**
 * \brief Create and open a new Unix domain client socket to the specified
 * address/path.
 *
 * `dsuInitClientSocket` will block for a connection.
 *
 * \param dsuSocket Memory to return the new socket in.
 * \param socketPath Path to the Unix domain socket to connect to.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus
dsuInitClientSocket(struct DsuSocket* dsuSocket, char* socketPath);

/**
 * \brief Close a DSU socket.
 *
 * \param dsuSocket Socket to close.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus
dsuDestroySocket(struct DsuSocket* dsuSocket);

/**
 * \brief Set up and open the socket the DSU server will use to listen for
 * incoming patch requests.
 *
 * \param dsuSocket Pointer to memory to store the new socket's details in.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus
dsuDestroyServerSocket(struct DsuServerSocket* dsuSocket);

/**
 * \brief Check if a DSU server has incoming connections.
 *
 * DSU server connections are used to send patch requests.
 *
 * \param dsuSocket The socket to test.
 * \returns `true` if the socket has pending connections.
 */
bool
dsuServerConnectionPending(struct DsuServerSocket* dsuSocket);

/**
 * \brief Accept an incoming connection and create a new socket
 * to communicate with the remote client.
 *
 * \param serverSocket The server socket to accept from.
 * \param clientSocket Memory to store details for the new socket.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus
dsuServerAcceptConnection(struct DsuServerSocket* serverSocket,
                          struct DsuSocket* clientSocket);

/**
 * Write a DSU packet to a socket.
 *
 * \param socket The socket to write to.
 * \param packet The packet to send over the socket.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus
dsuSocketWritePacket(struct DsuSocket* socket, union DsuPacket* packet);

/**
 * Read a DSU packet from the socket.
 *
 * \param socket The socket to read from,
 * \param buffer Memory to store a read packet into.
 * \param bufferLen Length of the `buffer`.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus
dsuSocketReadPacket(struct DsuSocket* socket, union DsuPacket* packet);
#endif
