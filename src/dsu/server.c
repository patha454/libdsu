#include "dsu/socket.h"
#include "dsu/status.h"
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  struct DsuServerSocket socket;
  struct DsuClientSocket client;
  if (dsuInitServerSocket(&socket) != DSU_SUCCESS) {
    fprintf(stderr, "Error creating server socket");
  }
  if (dsuInitClientSocket(&client, socket.filePath) != DSU_SUCCESS) {
    fprintf(stderr, "Error opening client socket");
  }
  if (dsuServerConnectionPending(&socket)) {
    fprintf(stdout, "Connection pending");
  }
  if (dsuDestroyServerSocket(&socket) != DSU_SUCCESS) {
    fprintf(stderr, "Error closing server socket");
  }
  return EXIT_SUCCESS;
}
