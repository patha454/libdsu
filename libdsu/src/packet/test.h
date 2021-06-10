/**
 * \file test.h
 *
 * `test.h` defines a test packet used for debugging DSU packet
 * communication.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 */

#ifndef PACKET_DUMMY_H_
#define PACKET_DUMMY_H_

#include "packet/header.h"
#include <stdint.h>

#define DSU_TEST_PACKET_PAYLOAD_LENGTH 256

/**
 * \brief A dummy packet used for testing and debugging packet communication.
 */
struct DsuPacketTest
{
  /** \brief Packet metadata. */
  struct DsuPacketHeader header;

  /** \brief Generic payload data. */
  uint8_t payload[DSU_TEST_PACKET_PAYLOAD_LENGTH];
};

#endif
