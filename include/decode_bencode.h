#ifndef DECODE_BENCODE
#define DECODE_BENCODE

typedef struct BencodeList bencodelist_t;
typedef struct BencodeDictionary bencodedict_t;
typedef struct BencodeData bencode_t;
typedef enum Type type;

bencode_t *decode_string(const char **bencoded);
bencode_t *decode_integer(const char **bencoded);
bencode_t *decode_list(const char **bencoded);
bencode_t *decode_dictionary(const char **bencoded);
bencode_t *decode_bencode(const char **bencoded);
#endif // !DECODE_BENCODE
