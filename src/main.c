#include "decode_bencode.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <bencoded string>\n", argv[0]);
    return 1;
  }

  char *out = decode_bencode((const char **)&argv[1]);
  printf("%s\n", out);
  free(out);

  return 0;
}
