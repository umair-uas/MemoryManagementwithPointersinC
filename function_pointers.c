#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { EE, CS, TELECOM, ELECTRONICS } Discipline;

typedef struct {
  int semsester;
  char* name;
  Discipline discipline;
  void (*showSubjects)();
} Student;

void show_cs_subjects();
void show_ee_subjects();
void show_telecom_subjects();
void show_electronics_subjects();
const char* getDiscipline(Discipline discipline);

void usage(const char* programName) {
  printf("Usage : %s <discipline>\n", programName);
  printf("Available disciplines: \n");
  printf(
      "cs: Computer Science, ee: Electrical Engineering, el: Electronics, "
      "te: Telecommunications\n");
}
int main(int argc, char** argv) {
  if (argc <= 1) {
    usage(argv[0]);
    return 1;
  }
  Student s1;
  s1.semsester = 3;
  const char* sname = "Freddie";
  s1.name = malloc(strlen(sname) + 1);
  if (s1.name == NULL) {
    perror("Malloc failed");
    return 1;
  }
  strncpy(s1.name, sname, strlen(sname));

  if (!strcmp("cs", argv[1])) {
    s1.discipline = CS;
  } else if (!strcmp("ee", argv[1])) {
    s1.discipline = EE;
  } else if (!strcmp("te", argv[1])) {
    s1.discipline = TELECOM;
  } else if (!strcmp("el", argv[1])) {
    s1.discipline = ELECTRONICS;
  } else {
    printf("Invalid discipline.\n");
    usage(argv[0]);

    free(s1.name);
    return 1;
  }
  void (*subjectsFunction[4])() = {show_cs_subjects, show_ee_subjects,
                                   show_telecom_subjects,
                                   show_electronics_subjects};

  s1.showSubjects = subjectsFunction[s1.discipline];
  printf("Semester: %d\n", s1.semsester);
  printf("Name : %s\n", s1.name);
  printf("Discipline: %s\n", getDiscipline(s1.discipline));
  // call the showSubjects function
  printf("Subjects: \n");
  s1.showSubjects();

  free(s1.name);
  s1.name = NULL;
  return 0;
}

const char* getDiscipline(Discipline discipline) {
  switch (discipline) {
    case CS: /* constant-expression */
      return "Computer Science";
      break;
    case EE:
      return "Electrical Engineering";
      break;
    case TELECOM:
      return "Telecommunication Engineering";
    case ELECTRONICS:
      return "Electronics Engineering";
    default:
      return "Unknown Discipline";
  }
}
void show_cs_subjects() {
  printf(
      "\t Computer Architecture, Embedded System Design,Data Structures and "
      "Algorithms \n");
}
void show_ee_subjects() {
  printf(
      "\t DSP,Basic Electronics, Fundamentals of Electrical Engineering, "
      "Cicruit Theory \n");
}
void show_telecom_subjects() {
  printf(
      "\t Wireless Communication, Mobile Communication,Optical Communication, "
      "Antenna and Microwave Engineering,Radar,Information Networks\n");
}
void show_electronics_subjects() {
  printf(
      "\t Basic Electronic, Digital Electronics, Microcontrollers and "
      "Embedded Systems,Analog Circuit Design,Power Electronics \n");
}
