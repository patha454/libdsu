#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char** argv)
{
  printf("Hello, world");
  printf("%s, %s", argv[1], argv[2]);
  return EXIT_SUCCESS;
}