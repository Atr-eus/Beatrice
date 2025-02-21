#include "utility.h"
#include "decode_bencode.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool is_char_digit(char c) { return c >= '0' && c <= '9'; }

void throw_error(char *msg) {
  fprintf(stderr, "%s", msg);
  exit(1);
}

void print_indent(uint8_t indent) {
  for (uint32_t i = 0; i < indent; ++i)
    printf("  ");
}

void print_list(const bencodelist_t *decoded_list, uint8_t indent) {
  printf("[\n");

  while (decoded_list) {
    print_indent(indent + 1);
    print_bencode(decoded_list->data, indent + 1);
    decoded_list = decoded_list->next;
  }

  print_indent(indent);
  printf("]\n");
}

void print_dictionary(const bencodedict_t *decoded_dictionary, uint8_t indent) {
  printf("{\n");

  while (decoded_dictionary) {
    print_indent(indent + 1);
    printf("\"%s\": ", decoded_dictionary->key);
    print_bencode(decoded_dictionary->value, indent + 1);
    decoded_dictionary = decoded_dictionary->next;
  }

  print_indent(indent);
  printf("}\n");
}

void print_bencode(const bencode_t *decoded, uint8_t indent) {
  if (!decoded)
    return;

  switch (decoded->type) {
  case BENCODE_INTEGER:
    printf("%ld\n", decoded->data.integer);
    break;
  case BENCODE_STRING:
    printf("\"%s\"\n", decoded->data.string);
    break;
  case BENCODE_LIST:
    print_list(decoded->data.list, indent);
    break;
  case BENCODE_DICTIONARY:
    print_dictionary(decoded->data.dict, indent);
    break;
  }
}
