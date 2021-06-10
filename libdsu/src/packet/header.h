/**
 * \file header.h
 *
 * `header.h` defines a common header shared by all DSU packets.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 */

#include "packet/types.h"
#include <stddef.h>

#ifndef PACKET_HEADER_H_
#define PACKET_HEADER_H_

/**
 * \brief Common header shared by all DSU packets.
 */
typedef struct DsuPacketHeader
{
  /** \brief The type of packet attached to the header. */
  DsuPacketType type;

  /**
   *  \brief The length of the packet following the header.
   *
   * A length field may seem redundant alongside `type`. Including the length
   * in the header allows for variable length packets, and prevents us
   * exhaustive lookups based on `type` when we want to know the size of a
   * particular packet.
   * */
  size_t length;
} DsuPacketHeader;

#endif
