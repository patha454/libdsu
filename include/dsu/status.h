/**
 * \file status.h
 * \brief `dsu/status.h` defines the `DsuStatus` enum, and functions for
 * manipulating status codes.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>.
 * \copyright BSL-1.0.
 */

#ifndef DSU_STATUS_H_
#define DSU_STATUS_H_

/** \brief `DsuStatus` indicates the success or failure of DSU tasks. */
typedef enum DsuStatus
{
    /** \brief Action successful. No error to report. */
    DSU_SUCCESS,

    /** \brief Error creating, opening, or destroying sockets. */
    DSU_ERROR_SOCKET,

    /** \brief Error allocating memory. */
    DSU_ERROR_MEMORY,

    /** \brief Unexpected or unrecoverable error. */
    DSU_PANIC
} DsuStatus;

#endif
