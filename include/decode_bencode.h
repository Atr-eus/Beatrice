#ifndef DECODE_BENCODE
#define DECODE_BENCODE

#include <stdint.h>

typedef struct BencodeList bencodelist_t;
typedef struct BencodeDictionary bencodedict_t;
typedef struct BencodeData bencode_t;
typedef enum Type type;

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

bencode_t *decode_string(const char **bencoded);

bencode_t *decode_integer(const char **bencoded);

bencode_t *decode_list(const char **bencoded);

bencode_t *decode_dictionary(const char **bencoded);

bencode_t *decode_bencode(const char **bencoded);

#endif // !DECODE_BENCODE
