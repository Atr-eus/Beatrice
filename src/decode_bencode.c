#include "decode_bencode.h"
#include "utility.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decode_string(const char **bencoded) {
  const size_t content_length = atoi(*bencoded);
  const char *separator_ptr = strchr(*bencoded, ':');

  if (separator_ptr != NULL) {
    char *decoded = (char *)malloc(content_length + 1);
    strncpy(decoded, separator_ptr + 1, content_length);
    decoded[content_length] = '\0';

    return decoded;
  } else {
    throw_error("Invalid input.\n");

    return NULL;
  }
}

char *decode_integer(const char **bencoded) {
  const size_t content_length = strlen(*bencoded) - 2;

  char *decoded = (char *)malloc(content_length + 1);
  strncpy(decoded, *bencoded + 1, content_length);
  decoded[content_length] = '\0';

  return decoded;
}

char *decode_list(const char **bencoded) { return "hello list"; }

char *decode_dictionary(const char **bencoded) { return "hello dictionary"; }

char *decode_bencode(const char **bencoded) {
  const char first = *bencoded[0], last = *(*bencoded + strlen(*bencoded) - 1);

  if (is_char_digit(*bencoded[0])) {
    return decode_string(bencoded);
  } else if (first == 'i' && last == 'e') {
    return decode_integer(bencoded);
  } else if (first == 'l' && last == 'e') {
    return decode_list(bencoded);
  } else if (first == 'd' && last == 'e') {
    return decode_dictionary(bencoded);
  } else {
    throw_error("Invalid input.\n");

    return NULL;
  }
}
