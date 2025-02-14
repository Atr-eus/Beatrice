#include "decode_bencode.h"
#include <curses.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: ./program <bencoded string>\n");
    return 1;
  }

  char *out = decode_bencode(argv[1]);
  printf("%s\n", out);

  return 0;
}
