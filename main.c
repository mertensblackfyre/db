#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "helpers.h"
#include "kv.h"

#define SIZE 1024
unsigned char _page[PAGE_SIZE];
/*
  char *input;

  do {
    input = readline("> ");
    if (input == NULL || strlen(input) == 0)
      continue;

    printf("%s\n", input);
    free(input);
  } while (true);

 */
int main(void) {

  size_t offset = 11;
  _data *kv1 = malloc(sizeof(_data));
  kv1->key = calloc(4, sizeof(char));
  kv1->value = calloc(4, sizeof(char));

  strcpy((char *)kv1->key, "id");
  strcpy((char *)kv1->value, "42");

  kv1->value_length = 4;
  kv1->key_length = 4;

  serialize(kv1, &offset);

  printf("Successfully packed item into page. Total bytes written: %zu\n",
         offset);
  free(kv1->key);
  free(kv1->value);
  free(kv1);

  return EXIT_SUCCESS;
}
