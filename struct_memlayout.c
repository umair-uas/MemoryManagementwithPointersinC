#include <stddef.h>
#include <stdio.h>

typedef struct {
  char letter;
  unsigned int rank;
} Grade;

int main() {
  // Declare and initialize struct on stack
  const Grade student_grade = {.letter = 'A', .rank = 91};

  // Show values of struct members
  printf("\nLetter: %-10c\n", student_grade.letter);
  printf("Rank:   %-10d\n", student_grade.rank);

  // Get size of struct members and
  const size_t letter_size = sizeof(student_grade.letter);
  const size_t rank_size = sizeof(student_grade.rank);
  const size_t student_grade_size = sizeof(student_grade);

  printf("Size of student_grade.letter: %zu\n", letter_size);
  printf("Size of student_grade.rank: %zu\n", rank_size);
  printf("Size of student_grade: %zu\n", student_grade_size);

  // Calcuate struct padding
  const size_t student_grade_struct_padding =
      student_grade_size - letter_size - rank_size;
  printf("Padding in Grade struct: %zu\n", student_grade_struct_padding);

  // Show memory addresses of struct members
  printf("Address of student_grade struct : %p\n", &student_grade);
  printf("Address of student_grade letter member : %p\n",
         &student_grade.letter);
  printf("Address of student_grade rank member : %p\n", &student_grade.rank);

  // Calculate the padding via memory offsets using offsetof macro from stddef.h

  const size_t letter_offset = offsetof(Grade, letter),
               rank_offset = offsetof(Grade, rank),
               padding = rank_offset - (letter_offset + letter_size);

  printf(" Letter byte offset:  \t %zu\n", letter_offset);
  printf(" Rank byte offset:  \t %zu\n", rank_offset);
  printf("Total padding of struct Grade: %zu\n", padding);
  printf("-------------------------------------\n");
  printf("| letter: %zu | padding: %zu | rank: %zu |\n", letter_size, padding,
         rank_size);
  printf("-------------------------------------\n");
  return 0;
}
