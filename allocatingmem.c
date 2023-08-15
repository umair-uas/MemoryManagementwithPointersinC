#include <stdio.h>
#include <stdlib.h>

void malloc_int_dangerous(int* ptrtoInt);
int malloc_int_safe(int** ptrtoInt);
int* maloc_int_safe_by_return_modified(void);  // Changed function name

int main() {
  int* ptrtoMyNum;
  int myNum = 0;
  ptrtoMyNum = &myNum;
  printf("Inside [%s:%d] : ptrtoMyNum : %p\n", __func__, __LINE__, ptrtoMyNum);
  malloc_int_dangerous(ptrtoMyNum);
  printf("Inside [%s:%d] : ptrtoMyNum : %p\n", __func__, __LINE__, ptrtoMyNum);

  int* ptrtoSafeInt =
      maloc_int_safe_by_return_modified();  // Using the new function name

  printf("Inside [%s:%d] : ptrtoSafeInt : %p\n", __func__, __LINE__,
         ptrtoSafeInt);
  free(ptrtoSafeInt);

  int* ptrsafemalloc;
  if (malloc_int_safe(&ptrsafemalloc) == 0) {
    printf("Inside main: ptrsafemalloc address: %p\n", &ptrsafemalloc);
    printf("Inside main: ptrsafemalloc value: %p\n", ptrsafemalloc);
    free(ptrsafemalloc);
  } else {
    fprintf(stderr, "Memory allocation failed\n");
  }
  return 0;
}

void malloc_int_dangerous(int* ptrtoInt) {
  ptrtoInt = malloc(sizeof(int) * 2);
  printf("Inside [%s:%d] : ptrtoInt : %p\n", __func__, __LINE__, ptrtoInt);
  printf(
      " Memory leak here, because ptrtoInt goes out of scope and is never "
      "freed !!\n");

  // free(ptrtoInt);
}
int malloc_int_safe(int** ptrtoInt) {
  *ptrtoInt = malloc(sizeof(int));
  if (*ptrtoInt == NULL) {
    return 1;
  }
  printf("Inside malloc_int_safe: ptrtoInt address: %p\n", &ptrtoInt);
  printf("Inside malloc_int_safe: ptrtoInt value: %p\n", ptrtoInt);
  printf(
      "Inside malloc_int_safe: *ptrtoInt value (allocated memory address): "
      "%p\n",
      *ptrtoInt);
  return 0;
}
int* maloc_int_safe_by_return_modified(void) {
  int* ptrtoInt = malloc(sizeof(int));
  printf("Inside [%s:%d] : ptrtoInt : %p\n", __func__, __LINE__, ptrtoInt);
  return ptrtoInt;
}