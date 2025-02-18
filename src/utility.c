#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

bool is_char_digit(char c) { return c >= '0' && c <= '9'; }

void throw_error(char *msg) {
  fprintf(stderr, "%s", msg);
  exit(1);
}
