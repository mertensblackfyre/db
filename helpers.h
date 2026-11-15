
#ifndef HELPERS_H
#define HELPERS_H

#include "kv.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

static inline int serialize(_data *data, size_t *offset) {
  size_t key_len = strlen((char *)data->key);
  memcpy(_page + *offset, &key_len, sizeof(size_t));
  *offset += sizeof(size_t);

  memcpy(_page + *offset, data->key, key_len);
  *offset += key_len;

  return 0;
};

static inline int deserialize(_data *data);

#endif
