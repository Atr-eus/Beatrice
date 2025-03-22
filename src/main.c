#include "decode_bencode.h"
#include "handle_parsed.h"
#include "utility.h"
#include <curses.h>
#include <stddef.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <bencoded string>\n", argv[0]);
    return 1;
  }

  // const char *bencoded = argv[1];
  // bencode_t *out = decode_bencode((const char **)&argv[1]);
  const char *bencoded = read_torrent(argv[1]);
  bencode_t *out = decode_bencode(&bencoded);
  print_bencode(out, 0);

  bencode_t *infodict = find_by_key(out->data.dict, "info");
  print_bencode(infodict, 0);

  printf("%s\n", encode_bencode(infodict));
  printf("%s\n", get_info_hash(infodict));

  return 0;
}
