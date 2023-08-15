#include <stdio.h>
#include <stdlib.h>

void print_memory_info(const char* label, const void* ptr) {
  printf("%s: Address = %p\n", label, ptr);
}

void print_values(const int* ptr, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    printf("Value: %d at address: %p\n", ptr[i], (const void*)&ptr[i]);
  }
}

int main() {
  const int initial_count = 4;
  int* my_ptr = malloc(sizeof(int) * initial_count);
  if (my_ptr == NULL) {
    perror("Malloc failed");
    exit(EXIT_FAILURE);
  }
  print_memory_info("Allocated memory", my_ptr);

  for (size_t i = 0; i < initial_count; i++) {
    my_ptr[i] = i;
    printf("Added value %zu to address: %p\n", i, (const void*)&my_ptr[i]);
  }

  const int num_count = 4;
  int* my_ptr_calloced = calloc(num_count, sizeof(int));
  if (my_ptr_calloced == NULL) {
    perror("Calloc failed");
    exit(EXIT_FAILURE);
  }
  print_memory_info("Allocated memory", (const void*)my_ptr_calloced);

  for (size_t i = 0; i < num_count; i++) {
    my_ptr_calloced[i] = i * 11;
    printf("Value %d at address: %p\n", my_ptr_calloced[i],
           (const void*)&my_ptr_calloced[i]);
  }

  const int resize_count = num_count + 2;
  int* resized_ptr = realloc(my_ptr, sizeof(int) * resize_count);
  if (resized_ptr == NULL) {
    perror("Realloc failed");
    exit(EXIT_FAILURE);
  }
  print_memory_info("Resized memory", resized_ptr);

  printf("Values in realloced block:\n");
  print_values(resized_ptr, resize_count);
  const int realloc_count = num_count - 2;
  int* realloced_ptr = realloc(my_ptr_calloced, sizeof(int) * realloc_count);
  if (realloced_ptr == NULL) {
    perror("Realloc failed");
    exit(EXIT_FAILURE);
  }
  print_memory_info("Resized memory", realloced_ptr);

  printf("Values in realloced block after reallocation:\n");
  print_values(realloced_ptr, realloc_count);

  free(resized_ptr);
  free(realloced_ptr);
  return 0;
}
