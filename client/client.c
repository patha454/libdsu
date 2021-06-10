/**
 * \file client.c
 *
 * \brief DSU client tool to work with libdsu libraries.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 */

#include "dsu/packet.h"
#include "dsu/socket.h"
#include "dsu/status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char** argv)
{
  (void)(argc);
  struct DsuSocket socket;
  struct DsuDummyPacket testPacket;
  strcpy(testPacket.payload, "dkeadbeed");
  testPacket.header.length = sizeof(struct DsuDummyPacket);
  testPacket.header.type = DSU_PACKET_DUMMY;
  if (dsuInitClientSocket(&socket, argv[1]) != DSU_SUCCESS) {
    fprintf(stderr, "Error opening socket\n");
  }
  if (dsuSocketWritePacket(&socket, (struct DsuPacketHeader*)&testPacket) !=
      DSU_SUCCESS) {
    fprintf(stderr, "Error sending packet.\n");
  }
  dsuDestroySocket(&socket);
  return EXIT_SUCCESS;
}
