#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_NAME_LENGTH 100

typedef struct {
  char name[MAX_AUTHOR_NAME_LENGTH];
} Author;

typedef struct {
  char title[MAX_TITLE_LENGTH];
  Author* author;
} Book;

typedef struct {
  Book* books;
  size_t numBooks;
} Library;

Author* create_author(const char* name);
Book* create_book(const char* title, Author* author);
void clean_library(Library* library);

int main() {
  size_t numBooks;
  printf("Enter the number of books: ");
  scanf("%zu", &numBooks);
  getchar();  // Consume the newline left in the buffer

  Library library;
  library.numBooks = numBooks;
  library.books = (Book*)malloc(numBooks * sizeof(Book));

  for (size_t i = 0; i < numBooks; i++) {
    char input[100];
    char title[MAX_TITLE_LENGTH];
    char authorName[MAX_AUTHOR_NAME_LENGTH];

    printf("Enter title and author of book %zu (format: Title, Author): ",
           i + 1);
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%[^,], %[^\n]", title, authorName);

    Author* author = create_author(authorName);
    Book* book = create_book(title, author);

    library.books[i] = *book;
  }

  printf("Enter the book number (1 to %zu): ", numBooks);
  size_t bookChoice;
  scanf("%zu", &bookChoice);

  if (bookChoice >= 1 && bookChoice <= numBooks) {
    const Book selectedBook = library.books[bookChoice - 1];
    printf("Selected Book:\n");
    printf("Title: %s\n", selectedBook.title);
    printf("Author: %s\n", selectedBook.author->name);
  } else {
    printf("Invalid choice.\n");
  }

  clean_library(&library);

  return 0;
}

Author* create_author(const char* name) {
  Author* author = (Author*)malloc(sizeof(Author));
  if (author) {
    strncpy(author->name, name, sizeof(author->name));
    author->name[sizeof(author->name) - 1] = '\0';  // Ensure null-termination
  }
  return author;
}

Book* create_book(const char* title, Author* author) {
  Book* book = (Book*)malloc(sizeof(Book));
  if (book) {
    strncpy(book->title, title, sizeof(book->title));
    book->title[sizeof(book->title) - 1] = '\0';  // Ensure null-termination
    book->author = author;
  }
  return book;
}

void clean_library(Library* library) {
  free(library->books);
}
