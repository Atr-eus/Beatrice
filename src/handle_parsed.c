#include "handle_parsed.h"
#include "decode_bencode.h"
#include "utility.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("%s: ", decoded_dictionary->key);
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
    printf("%s\n", decoded->data.string);
    break;
  case BENCODE_LIST:
    print_list(decoded->data.list, indent);
    break;
  case BENCODE_DICTIONARY:
    print_dictionary(decoded->data.dict, indent);
    break;
  }
}

char *encode_integer(int64_t n) {
  char buf[64];
  snprintf(buf, sizeof(buf), "i%" PRId64 "e", n);

  return strdup(buf);
}

char *encode_string(const char *s) {
  size_t len = strlen(s);
  size_t size_len = snprintf(NULL, 0, "%zu:", len);

  char *res = malloc(len + size_len + 1);
  snprintf(res, size_len + 1, "%zu:", len);
  memcpy(res + size_len, s, len + 1);

  return res;
}

char *encode_list(bencodelist_t *list) {
  char *res = strdup("l");

  bencodelist_t *it = list;
  while (it) {
    char *encoded = encode_bencode(it->data);
    res = realloc(res, strlen(res) + strlen(encoded) + 1);
    strcat(res, encoded);
    free(encoded);

    it = it->next;
  }

  res = realloc(res, strlen(res) + 2);
  strcat(res, "e");

  return res;
}

char *encode_dictionary(bencodedict_t *dict) {
  char *res = strdup("d");

  bencodedict_t *it = dict;
  while (it) {
    char *key = encode_string(it->key);
    char *val = encode_bencode(it->value);

    res = realloc(res, strlen(res) + strlen(key) + strlen(val) + 1);
    strcat(res, key);
    strcat(res, val);
    free(key);
    free(val);

    it = it->next;
  }

  res = realloc(res, strlen(res) + 2);
  strcat(res, "e");
  return res;
}

char *encode_bencode(bencode_t *decoded) {
  switch (decoded->type) {
  case BENCODE_INTEGER:
    return encode_integer(decoded->data.integer);
  case BENCODE_STRING:
    return encode_string(decoded->data.string);
  case BENCODE_LIST:
    return encode_list(decoded->data.list);
  case BENCODE_DICTIONARY:
    return encode_dictionary(decoded->data.dict);
  default:
    return NULL;
  }
}

bencode_t *find_by_key(bencodedict_t *dict, const char *target) {
  while (dict != NULL) {
    if (strcmp(dict->key, target) == 0) {
      return dict->value;
    }

    dict = dict->next;
  }

  return NULL;
}
