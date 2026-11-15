
#ifndef HELPERS_H
#define HELPERS_H

#include "kv.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

static inline int serialize(_data *data, size_t *offset) {

  memcpy(_page + *offset, &data->key, data->key_length);
  offset += data->key_length;

  memcpy(_page + *offset, &data->value, data->value_length);
  offset += data->value_length;

  return 0;
};
static inline int deserialize(_data *data);

#endif
