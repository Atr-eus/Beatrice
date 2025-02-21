#include "utility.h"
#include "decode_bencode.h"
#include <stdio.h>
#include <stdlib.h>

bool is_char_digit(char c) { return c >= '0' && c <= '9'; }

void throw_error(char *msg) {
  fprintf(stderr, "%s", msg);
  exit(1);
}

void print_indent() { printf("  "); }

void print_list(const bencodelist_t *decoded_list) {
  printf("[\n");

  while (decoded_list) {
    print_indent();
    print_bencode(decoded_list->data);
    decoded_list = decoded_list->next;
  }

  printf("]\n");
}

void print_dictionary(const bencodedict_t *decoded_dictionary) {
  printf("{\n");

  while (decoded_dictionary) {
    print_indent();
    printf("\"%s\": ", decoded_dictionary->key);
    print_bencode(decoded_dictionary->value);
    decoded_dictionary = decoded_dictionary->next;
  }

  printf("}\n");
}

void print_bencode(const bencode_t *decoded) {
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
    print_list(decoded->data.list);
    break;
  case BENCODE_DICTIONARY:
    print_dictionary(decoded->data.dict);
    break;
  }
}
