#include <stdio.h>
#include <stdlib.h>

void print_int_by_ref(int* ptrtoInt);
void print_int_by_value(int num);
int main() {
  int mynum = 10;
  printf("Inside %s \n", __func__);
  printf(" Int: Address : %p | Value: %d\n", &mynum, mynum);
  print_int_by_ref(&mynum);
  //   print_int_by_value(mynum);

  printf(" now back in main ---> Int: Address : %p | Value: %d\n", &mynum,
         mynum);
  print_int_by_ref(&mynum);
  return 0;
}
void print_int_by_ref(int* ptrtoInt) {
  printf("Inside %s \n", __func__);
  printf("Int : Address : %p | Value: %d\n", ptrtoInt, *ptrtoInt);
  *ptrtoInt = 20;
  ptrtoInt = NULL;
  printf("Pointer inside %s after: %p\n", __func__, ptrtoInt);
}
void print_int_by_value(int mynum) {
  printf("Inside %s \n", __func__);
  printf("Int: Address: %p | Value : %d\n", &mynum, mynum);
  mynum = 40;
  printf("Int: Address: %p | Value : %d\n", &mynum, mynum);
}