#include "decode_bencode.h"
#include "utility.h"
#include <curses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <bencoded string>\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    throw_error("fopen error!\n");
    fclose(fp);
    return EXIT_FAILURE;
  }

  fseek(fp, 0, SEEK_END);
  size_t fsize = ftell(fp);
  rewind(fp);

  char *buf = malloc(fsize + 1);
  if (buf == NULL) {
    throw_error("malloc error!\n");
    fclose(fp);
    return EXIT_FAILURE;
  }
  size_t rsize = fread(buf, 1, fsize, fp);
  buf[rsize] = '\0';
  fclose(fp);

  // bencode_t *out = decode_bencode((const char **)&argv[1]);
  bencode_t *out = decode_bencode((const char **)&buf);
  print_bencode(out, 0);
  free(out);

  return 0;
}
