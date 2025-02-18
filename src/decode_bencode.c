#include "decode_bencode.h"
#include "utility.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Type {
  BENCODE_INTEGER,
  BENCODE_STRING,
  BENCODE_LIST,
  BENCODE_DICTIONARY
} type;

typedef struct BencodeList {
  bencode_t *data;
  bencodelist_t *next;
} bencodelist_t;

typedef struct BencodeDictionary {
  char *key;
  bencode_t *value;
  bencodedict_t *next;
} bencodedict_t;

typedef struct BencodeData {
  type type;
  union {
    int64_t integer;
    char *string;
    bencodelist_t *list;
    bencodedict_t *dict;
  } data;
} bencode_t;

bencode_t *decode_integer(const char **bencoded) {
  (*bencoded)++;
  char *it;
  auto data = strtoll(*bencoded, &it, 10);

  if (*it != 'e')
    return NULL;
  *bencoded = it + 1;

  auto res = (bencode_t *)malloc(sizeof(bencode_t));
  res->type = BENCODE_INTEGER;
  res->data.integer = data;

  return res;
}

bencode_t *decode_string(const char **bencoded) {
  char *it;
  size_t content_length = strtol(*bencoded, &it, 10);

  if (*it != ':' || content_length < 0)
    return NULL;
  *bencoded = it + 1;

  auto res = (bencode_t *)malloc(sizeof(bencode_t));
  res->type = BENCODE_STRING;
  res->data.string = strndup(*bencoded, content_length);
  *bencoded += content_length;

  return res;
};

bencode_t *decode_list(const char **bencoded) {
  (*bencoded)++;

  // printf("[");
  bencodelist_t *head = NULL, **current = &head;
  while (**bencoded != 'e') {
    bencode_t *data = decode_bencode(bencoded);
    // switch (data->type) {
    // case BENCODE_INTEGER:
    //   printf("%ld", data->data.integer);
    //   break;
    // case BENCODE_STRING:
    //   printf("%s", data->data.string);
    //   break;
    // }
    // printf(",");

    *current = malloc(sizeof(bencode_t));
    (*current)->data = data;
    (*current)->next = NULL;
    current = &((*current)->next);
  }
  (*bencoded)++;

  auto res = (bencode_t *)malloc(sizeof(bencode_t));
  res->type = BENCODE_LIST;
  res->data.list = head;

  // printf("]");
  return res;
};

bencode_t *decode_dictionary(const char **bencoded) {
  (*bencoded)++;

  // printf("{\n");
  bencodedict_t *head = NULL, **current = &head;
  while (**bencoded != 'e') {
    bencode_t *key = decode_string(bencoded), *value = decode_bencode(bencoded);
    // printf("%s -> ", key->data.string);
    // value->type == BENCODE_STRING ? printf("%s\n", value->data.string)
    //                               : printf("%ld\n", value->data.integer);

    *current = malloc(sizeof(bencodedict_t));
    (*current)->key = key->data.string;
    (*current)->value = value;
    (*current)->next = NULL;
    current = &((*current)->next);
  }
  (*bencoded)++;

  bencode_t *res = malloc(sizeof(bencode_t));
  res->type = BENCODE_DICTIONARY;
  res->data.dict = head;

  // printf("}\n");
  return res;
};

bencode_t *decode_bencode(const char **bencoded) {
  if (**bencoded == 'i')
    return decode_integer(bencoded);
  else if (is_char_digit(**bencoded))
    return decode_string(bencoded);
  else if (**bencoded == 'l')
    return decode_list(bencoded);
  else if (**bencoded == 'd')
    return decode_dictionary(bencoded);
  else {
    throw_error("Invalid input format.\n");
    return NULL;
  }
}
