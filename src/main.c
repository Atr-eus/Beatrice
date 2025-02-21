#include "decode_bencode.h"
#include "utility.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <bencoded string>\n", argv[0]);
    return 1;
  }

  bencode_t *out = decode_bencode((const char **)&argv[1]);
  print_bencode(out, 0);
  free(out);

  return 0;
}
