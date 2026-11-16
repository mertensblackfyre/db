#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
#include "kv.h"

#define SIZE 1024
unsigned char _page[PAGE_SIZE];

int main(void) {
  size_t offset = 0;

  _data *kv1 = init_data((unsigned char *)"id", (unsigned char *)"42");
  if (kv1 == NULL) {
    perror("_data");
    return EXIT_FAILURE;
  };

  serialize(kv1, &offset);
  write_data(kv1, "db.db", offset);

  char *p = read_data("db.db", offset);
  deserialize(p, offset);

  free(kv1->key);
  free(kv1->value);
  free(kv1);
  return EXIT_SUCCESS;
}
