#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "helpers.h"
#include "kv.h"

#define SIZE 1024
unsigned char _page[PAGE_SIZE];

int main(void) {
  size_t offset = 0;
  _data *kv1 = malloc(sizeof(_data));

  kv1->key = calloc(4, sizeof(char));
  kv1->value = calloc(4, sizeof(char));

  strcpy((char *)kv1->key, "id");
  strcpy((char *)kv1->value, "42");

  kv1->key_length = strlen((char *)kv1->key);
  kv1->value_length = strlen((char *)kv1->value);
  serialize(kv1, &offset);

  FILE *file = fopen("hi.db", "wb");
  if (file == NULL) {
    perror("Failed to open hi.db");
    free(kv1->key);
    free(kv1->value);
    free(kv1);
    return -1;
  }

  size_t written = fwrite(_page, 1, offset, file);

  fclose(file);

  printf("Debug: Current offset is %zu bytes, wrote %zu bytes to disk.\n",
         offset, written);

  free(kv1->key);
  free(kv1->value);
  free(kv1);

  return EXIT_SUCCESS;
}
