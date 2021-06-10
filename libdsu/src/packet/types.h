/**
 * \file types.h
 *
 * `types.h` defines a data type for representing DSU packet types.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 */

#ifndef PACKET_TYPES_H_
#define PACKET_TYPES_H_

typedef enum DsuPacketType
{
  /** A lone header without a body. */
  DSU_PACKET_HEADER,

  /** A dummy test packet. */
  DSU_PACKET_TEST
} DsuPacketType;

#endif
