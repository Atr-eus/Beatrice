#include "decode_bencode.h"
#include "utility.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bencode_t *decode_integer(const char **bencoded) {
  (*bencoded)++;
  char *it;
  int64_t data = strtoll(*bencoded, &it, 10);

  if (*it != 'e')
    return NULL;
  *bencoded = it + 1;

  bencode_t *res = malloc(sizeof(bencode_t));
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

  bencode_t *res = malloc(sizeof(bencode_t));
  res->type = BENCODE_STRING;
  res->data.string = strndup(*bencoded, content_length);
  *bencoded += content_length;

  return res;
};

bencode_t *decode_list(const char **bencoded) {
  (*bencoded)++;

  bencodelist_t *head = NULL, **current = &head;
  while (**bencoded != 'e') {
    bencode_t *data = decode_bencode(bencoded);

    *current = malloc(sizeof(bencodelist_t));
    (*current)->data = data;
    (*current)->next = NULL;
    current = &((*current)->next);
  }
  (*bencoded)++;

  bencode_t *res = malloc(sizeof(bencode_t));
  res->type = BENCODE_LIST;
  res->data.list = head;

  return res;
};

bencode_t *decode_dictionary(const char **bencoded) {
  (*bencoded)++;

  bencodedict_t *head = NULL, **current = &head;
  while (**bencoded != 'e') {
    bencode_t *key = decode_string(bencoded), *value = decode_bencode(bencoded);

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
