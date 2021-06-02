#include <stdio.h>
#include <stdlib.h>
#include "dsuStatus.h"
#include "dsuSocket.h"

int main(void)
{
    struct DsuServerSocket socket;
    if (dsuInitServerSocket(&socket) != DSU_SUCCESS) {
        fprintf(stderr, "Error creating server socket");
    }
    if (dsuDestroyServerSocket(&socket) != DSU_SUCCESS) {
        fprintf(stderr, "Error closing server socket");
    }
    return EXIT_SUCCESS;
}