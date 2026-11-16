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

  FILE *file = fopen(file_name, "rb");

  if (file == NULL) {
    perror("Failed to open file");
    return NULL;
  }

  char *page = (char *)calloc(offset, sizeof(unsigned char));

  if (page == NULL) {
    perror("calloc");
    return NULL;
  }

  fread(page, 1, offset + 1, file);
  fclose(file);
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

static inline _data *deserialize(char *page, size_t offset) {

  size_t c_offset = 0;
  size_t value_len = 0;
  size_t key_len = 0;

  // key len
  memcpy(&key_len, page, sizeof(size_t));
  c_offset += sizeof(size_t) + key_len;

  // value len
  memcpy(&value_len, page + c_offset, sizeof(size_t));

  unsigned char *key =
      (unsigned char *)calloc(key_len+1, sizeof(unsigned char));
  if (key == NULL) {
    perror("calloc");
    return NULL;
  }

  // unsigned char *value =
  //   (unsigned char *)calloc(value_len + 1, sizeof(unsigned char));

  c_offset = sizeof(size_t);
  memcpy(key, page + c_offset, key_len+1);
  // c_offset += sizeof(size_t);
  // memcpy(&value, page + c_offset, value_len + 1);

  printf("%s\n", (char *)key);

  // printf("%d\n", (int)key_len);
  // printf("%d\n", (int)value_len);
  free(page);
  free(key);
  // free(value);
  return NULL;
};

#endif
