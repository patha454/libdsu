/**
 * \file socket.h
 * \brief `dsu/socket.h` provides an interface for creating and using sockets to
 * communicate with the DSU service.
 * 
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>.
 * \copyright BSL-1.0.
 */

#include "dsu/status.h"

#ifndef DSU_SOCKET_H_
#define DSU_SOCKET_H_

struct DsuServerSocket
{
    int fileDescriptor;
    char* filePath;
};

struct DsuClientSocket
{
    int fileDescriptor;
    char* filePath;
};

/**
 * \brief Create and open a new Unix domain server socket to listen for DSU
 * requests.
 *
 * \param dsuSocket Memory to return the new socket in.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus dsuInitServerSocket(struct DsuServerSocket* dsuSocket);

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
DsuStatus dsuInitClientSocket(struct DsuClientSocket* dsuSocket, char* socketPath);

/**
 * \brief Set up and open the socket the DSU server will use to listen for
 * incoming patch requests.
 *
 * \param dsuSocket Pointer to memory to store the new socket's details in.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus dsuDestroyServerSocket(struct DsuServerSocket* dsuSocket);

#endif
