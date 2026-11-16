#ifndef HELPERS_H
#define HELPERS_H

#include "kv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static inline _data *init_data(unsigned char *key, unsigned char *value) {

  size_t key_len = strlen((const char *)key);
  size_t val_len = strlen((const char *)value);

  _data *kv = (_data *)malloc(sizeof(_data));

  if (kv == NULL) {
    perror("malloc");
    return NULL;
  }

  kv->key = (unsigned char *)calloc(key_len + 1, sizeof(char));
  kv->value = (unsigned char *)calloc(val_len + 1, sizeof(char));

  if (kv->key == NULL || kv->value == NULL) {
    perror("calloc");
    return NULL;
  }

  strncpy((char *)kv->key, (char *)key, key_len);
  strncpy((char *)kv->value, (char *)value, val_len);

  kv->key_length = key_len;
  kv->value_length = val_len;

  return kv;
}

static inline void write_data(_data *kv, const char *file_name, size_t offset) {

  FILE *file = fopen(file_name, "wb");

  if (file == NULL) {
    perror("Failed to open file");
    free(kv->key);
    free(kv->value);
    free(kv);
    return;
  }
  fwrite(_page, 1, offset, file);
  fclose(file);
}

static inline char *read_data(const char *file_name, size_t offset) {

  char *page = (char *)calloc(offset, sizeof(char));
  if (page == NULL) {
    perror("calloc");
    return NULL;
  }

  FILE *file = fopen(file_name, "rb");

  if (file == NULL) {
    perror("Failed to open file");
    return NULL;
  }
  fread(page, 1, offset, file);
  return page;
}

static inline void serialize(_data *data, size_t *offset) {

  size_t key_len = strlen((char *)data->key);
  memcpy(_page + *offset, &key_len, sizeof(size_t));
  *offset += sizeof(size_t);

  memcpy(_page + *offset, data->key, key_len);
  *offset += key_len;

  size_t value_len = strlen((char *)data->value);
  memcpy(_page + *offset, &key_len, sizeof(size_t));
  *offset += sizeof(size_t);

  memcpy(_page + *offset, data->value, value_len);
  *offset += value_len;
};

static inline _data *deserialize(char *page) {
  printf("%s", page);
  return NULL;
};

#endif
