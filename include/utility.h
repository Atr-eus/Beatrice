#ifndef UTILITY
#define UTILITY

#include "decode_bencode.h"
#include <stdint.h>

bool is_char_digit(char c);

void throw_error(char *msg);

void print_indent(uint8_t indent);

void print_list(const bencodelist_t *decoded, uint8_t indent);

void print_dictionary(const bencodedict_t *decoded_list, uint8_t indent);

void print_bencode(const bencode_t *decoded_dictionary, uint8_t indent);

#endif // !UTILITY
