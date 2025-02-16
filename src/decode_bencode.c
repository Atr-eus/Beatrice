#include "decode_bencode.h"
#include "utility.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decode_integer(const char **bencoded);

char *decode_string(const char **bencoded);

char *decode_list(const char **bencoded);

char *decode_dictionary(const char **bencoded);

char *decode_bencode(const char **bencoded) {
  const char first = *bencoded[0], last = *bencoded[strlen(*bencoded) - 1];

  if (is_char_digit(*bencoded[0])) {
    return decode_string(bencoded);
  } else if (first == 'i' && last == 'e') {
    return decode_integer(bencoded);
  } else if (first == 'l' && last == 'e') {
    return decode_list(bencoded);
  } else if (first == 'd' && last == 'e') {
    return decode_dictionary(bencoded);
  } else {
    fprintf(stderr, "Invalid input.\n");
    exit(1);
  }
}
