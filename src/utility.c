#include "utility.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool is_char_digit(char c) { return c >= '0' && c <= '9'; }

void throw_error(char *msg) {
  fprintf(stderr, "%s", msg);
  exit(1);
}

char *read_torrent(const char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    throw_error("fopen error!\n");
    fclose(fp);

    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  size_t content_length = ftell(fp);
  rewind(fp);

  char *buf = malloc(content_length + 1);
  if (buf == NULL) {
    throw_error("malloc error!\n");
    fclose(fp);

    return NULL;
  }

  fread(buf, 1, content_length, fp);
  buf[content_length] = '\0';
  fclose(fp);

  return buf;
}
