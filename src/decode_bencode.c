#include "decode_bencode.h"
#include "utility.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decode_bencode(const char *bencoded) {
  if (is_char_digit(bencoded[0])) {
    // byte string encoding, format: <length>:<content>

    size_t len = atoi(bencoded);
    const char *separator_ptr = strchr(bencoded, ':');
    if (separator_ptr != NULL) {
      char *decoded = (char *)malloc(len + 1);
      strncpy(decoded, separator_ptr + 1, len);
      decoded[len] = '\0';

      return decoded;
    }
  }

  return "hello";
}
