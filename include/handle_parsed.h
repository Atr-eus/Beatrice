#ifndef HANDLE_PARSED
#define HANDLE_PARSED

#include "decode_bencode.h"
#include <stddef.h>

void print_indent(uint8_t indent);

void print_list(const bencodelist_t *decoded, uint8_t indent);

void print_dictionary(const bencodedict_t *decoded_list, uint8_t indent);

void print_bencode(const bencode_t *decoded_dictionary, uint8_t indent);

bencode_t *find_by_key(bencodedict_t *dict, const char *target);

#endif // !HANDLE_PARSED
