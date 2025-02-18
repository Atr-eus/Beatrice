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
  bencode_t *data;
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

  printf("%d, %ld\n", res->type, res->data.integer);

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

  printf("%d, %s\n", res->type, res->data.string);

  return res;
};

bencode_t *decode_list(const char **bencoded) {
  (*bencoded)++;

  bencodelist_t *head = NULL, **current = &head;
  while (**bencoded != 'e') {
    bencode_t *data = decode_bencode(bencoded);
    *current = malloc(sizeof(bencode_t));
    (*current)->data = data;
    (*current)->next = NULL;
    current = &((*current)->next);
  }
  (*bencoded)++;

  auto res = (bencode_t *)malloc(sizeof(bencode_t));
  res->type = BENCODE_LIST;
  res->data.list = head;

  return res;
};

bencode_t *decode_dictionary(const char **bencoded) {};

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
