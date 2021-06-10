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
  struct DsuServerSocket socket;
  struct DsuSocket client;
  struct DsuDummyPacket newPacket;
  if (dsuInitServerSocket(&socket) != DSU_SUCCESS) {
    fprintf(stderr, "Error creating socket.\n");
  }
  while (!dsuServerConnectionPending(&socket)) {
    printf("DSU server: Waiting for connection...\n");
    sleep(5);
  }
  if (dsuServerAcceptConnection(&socket, &client) != DSU_SUCCESS) {
    fprintf(stderr, "Error opening client connection\n");
  }
  if (dsuSocketReadPacket(&client, (uint8_t*)&newPacket, sizeof(newPacket)) !=
      DSU_SUCCESS) {
    fprintf(stderr, "Error reading packet from client.\n");
  }
  printf("Received packet with data %s\n", newPacket.payload);
  dsuDestroyServerSocket(&socket);
  dsuDestroySocket(&client);
  return EXIT_SUCCESS;
}
