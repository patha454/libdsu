#include "dsu/packet.h"
#include "dsu/socket.h"
#include "dsu/status.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

int
main(void)
{
  printf("a");
  struct DsuServerSocket socket;
  struct DsuSocket client;
  struct DsuSocket server;
  struct DsuDummyPacket testPacket;
  testPacket.header.length = sizeof(struct DsuDummyPacket);
  testPacket.header.type = DSU_PACKET_DUMMY;
  testPacket.payload[0] = 'a';
  testPacket.payload[1] = 'b';
  testPacket.payload[2] = 'b';
  testPacket.payload[3] = '\0';
  struct DsuDummyPacket newPacket;
  strcpy(newPacket.payload, "dkeadbeed");
  if (dsuInitServerSocket(&socket) != DSU_SUCCESS) {
    fprintf(stderr, "Error creating server socket\n");
  }
  if (dsuInitClientSocket(&client, socket.filePath) != DSU_SUCCESS) {
    fprintf(stderr, "Error opening client socket\n");
  }
  if (dsuServerConnectionPending(&socket)) {
    fprintf(stdout, "Connection pending\n");
  }
  if (dsuServerAcceptConnection(&socket, &server) != DSU_SUCCESS) {
    fprintf(stderr, "Failed to accept connection\n");
  }
  if (dsuSocketWritePacket(&client, (struct DsuPacketHeader*)&testPacket) !=
      DSU_SUCCESS) {
    fprintf(stderr, "Error sendin packet\n");
  }
  if (dsuSocketReadPacket(&server, (uint8_t*)&newPacket, sizeof(newPacket)) !=
      DSU_SUCCESS) {
    fprintf(stderr, "Error reading packet");
  }
  printf("Read back in %s\n", newPacket.payload);
  if (dsuDestroyServerSocket(&socket) != DSU_SUCCESS) {
    fprintf(stderr, "Error closing server socket\n");
  }
  return EXIT_SUCCESS;
}
