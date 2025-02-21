#ifndef UTILITY
#define UTILITY

#include "decode_bencode.h"

bool is_char_digit(char c);

void throw_error(char *msg);

void print_indent();

void print_list(const bencodelist_t *decoded);

void print_dictionary(const bencodedict_t *decoded_list);

void print_bencode(const bencode_t *decoded_dictionary);

#endif // !UTILITY
