#include <stdio.h>
#include <stdlib.h>

/*
Explanation:

You're dynamically allocating an array of integers using malloc.
This memory allocation creates a block of memory of size sizeof(int) *
count_block.

Pointer arithmetic is demonstrated by printing the addresses of the elements
in the allocated block, incremented by the size of int.
 This is used to traverse the memory locations sequentially.

You're finding the last address of the allocated block by adding the offset of
count_block - 1.

Values are assigned to the allocated memory using pointer arithmetic.

You're incrementing myPtr by 1 to demonstrate that this operation doesn't affect
the reference to the original allocated block.

A reference pointer ptrtoStart is used to keep track of the start of the
allocated block, and then myPtr is incremented.
This highlights the importance of maintaining the reference to the original
pointer if you perform operations that change the pointer.

The allocated memory is properly freed using the original pointer ptrtoStart to
avoid memory leaks.

The key takeaway is to maintain a reference to the original pointer returned by
malloc, perform pointer arithmetic operations on temporary pointers, and ensure
that you free the memory using the original pointer to prevent memory leaks.

*/

int main() {
  int count_block = 4;
  int* myPtr = malloc(sizeof(int) * count_block);  // dynamic array

  // 1. Simple pointer arithmetic, pointer incremented by size of type int (4
  // bytes on this machine)
  for (size_t i = 0; i < count_block; i++) {
    printf(" 'myPtr' address : %p\n", myPtr + i);
  }
  // 1.1  Find the last address of allocated block

  int* lastAddress = myPtr + count_block - 1;
  printf(" Last address of allocated block : %p\n", lastAddress);
  // 2.  assignig values to pointer
  // 3.  indexing and dereferencing with pointer arithmetic
  int initial_assigned_value = 5;
  for (size_t i = 0; i < count_block; i++) {
    *(myPtr + i) = initial_assigned_value;

    printf(" 'myPtr' [index=%zu] :: [mem location=%p] -> value %d\n", i,
           myPtr + i, *(myPtr + i));
  }

  /*
   myPtr++;// Beware this will move the pointer to the next location , and you
   will lose the original myPtr printf(" 'myPtr now points to %p\n",myPtr);
   // Don't forget to free allocated memory
   free(): invalid pointer
               Aborted

   free(myPtr);
   */

  int* ptrtoStart = myPtr;  // keep the reference to start of allocated block so
                            // you can free later.
  myPtr++;
  printf(" 'myPtr now points to %p\n", myPtr);
  free(ptrtoStart);
  return 0;
}
