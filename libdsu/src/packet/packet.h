/**
 * \file packet.h
 *
 * `packet.h` defines a union guaranteed to fit any known DSU packet.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "packet/header.h"
#include "packet/test.h"

/**
 * \brief `DsuPacket` represents a DSU packet.
 *
 * The union is guaranteed to fit any possible DSU packet.
 */
union DsuPacket
{
  /** The header of the packet. */
  struct DsuPacketHeader header;

  /** Access to the contents of a `dsuPacketTest` packet. */
  struct DsuPacketTest dsuPacketTest;
};

#endif
