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

/**
 * Get the name (file path) of the Unix domain socket used by the host
 * process.
 *
 * \param name Memory to copy the socket name into.
 * \param length Length of `name`.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus dsuInitServerSocket(struct DsuServerSocket* dsuSocket);

/**
 * \brief Set up and open the socket the DSU server will use to listen for
 * incoming patch requests.
 *
 * \param dsuSocket Pointer to memory to store the new socket's details in.
 * \returns `DSU_SUCCESS` or an error on failure.
 */
DsuStatus dsuDestroyServerSocket(struct DsuServerSocket* dsuSocket);

#endif
