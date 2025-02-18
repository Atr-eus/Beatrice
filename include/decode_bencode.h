#ifndef DECODE_BENCODE
#define DECODE_BENCODE

char *decode_string(const char **bencoded);
char *decode_integer(const char **bencoded);
char *decode_list(const char **bencoded);
char *decode_dictionary(const char **bencoded);
char *decode_bencode(const char **bencoded);
#endif // !DECODE_BENCODE
