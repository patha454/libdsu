/**
 * \brief `packet.h` defines packets used to communicate with the DSU server
 * embedded within a host program.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 */

#ifndef DSU_PACKET_H_
#define DSU_PACKET_H_

#include <stddef.h>

#define DUMMY_PACKET_STRING_LEN 255

/**
 * \brief Indicates the type of packet to a receiving program.
 */
typedef enum DsuPacketType
{
  DSU_PACKET_DUMMY
} DsuPacketType;

/**
 * \brief Common header for all DSU packets.
 */
typedef struct DsuPacketHeader
{
  /** \brief The type of packet proceeding the header. */
  DsuPacketType type;

  /** \brief The total length of the packet, including the header. */
  size_t packetLength;
} DsuPacketHeader;

/**
 * \brief Dummy packet for debugging purposes.
 */
typedef struct DsuDummyPacket
{
  /** \brief Packet metadata. */
  DsuPacketHeader header;

  /** Meaningless string. */
  char payload[DUMMY_PACKET_STRING_LEN];
} DsuDummyPacket;

#endif
