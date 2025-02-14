#include "decode_bencode.h"
#include "utility.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decode_bencode(const char *bencoded) {
  char *decoded;
  size_t bencoded_len = strlen(bencoded), content_len;

  if (is_char_digit(bencoded[0])) {
    // byte string encoding, format: <length>:<content>

    content_len = atoi(bencoded);
    const char *separator_ptr = strchr(bencoded, ':');
    if (separator_ptr != NULL) {
      decoded = (char *)malloc(content_len + 1);
      strncpy(decoded, separator_ptr + 1, content_len);
      decoded[content_len] = '\0';

      return decoded;
    } else {
      fprintf(stderr, "Invalid bencoded value: %s\n", bencoded);
      exit(1);
    }
  } else if (bencoded[0] == 'i' && bencoded[bencoded_len - 1] == 'e') {
    content_len = bencoded_len - 2;
    decoded = (char *)malloc(content_len + 1);
    strncpy(decoded, bencoded + 1, content_len);
    decoded[content_len] = '\0';

    return decoded;
  } else {
    fprintf(stderr, "Invalid bencoded value: %s\n", bencoded);
    exit(1);
  }
}
