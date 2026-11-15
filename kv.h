#ifndef KV_H
#define KV_H

#include <stddef.h>

#define PAGE_SIZE 4096

extern unsigned char _page[PAGE_SIZE];

typedef struct Node {
  unsigned char **keys;
  unsigned char **values;
  struct Node *children;
} _Node;

typedef struct _data {
  unsigned char *value;
  unsigned char *key;
  size_t value_length;
  size_t key_length;
} _data;

_data kv_get(unsigned char *key);
int kv_set(unsigned char *key, unsigned char *value);
int kv_delete(unsigned char *key);

/*

 type Iterator interface {
   HasNext() bool
   Next() (key []byte, val []byte)
    }
*/

#endif
