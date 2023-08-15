#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char* name;
} Subject;

typedef struct {
  const char* discipline;
  const Subject* subjects;
  size_t numSubjects;
} Discipline;

typedef struct {
  int semsester;
  char* name;
  const Discipline* discipline;

} Student;

void usage(const char* programName);
void show_subjects(const Student* student);

int main(int argc, char** argv) {
  if (argc <= 1) {
    usage(argv[0]);
    return 1;
  }

  // Define disciplines and subjects

  const Subject cs_subjects[] = {
      {"Computer Architecture"},           {"Embedded Systems Design"},
      {"Data Structures and Algorithms"},  {"Network Security "},
      {"Cryptography and Cyber Security"}, {"Advanced UNIX Programming"},
  };

  const Discipline cs_discipline = {"Computer Science", cs_subjects,
                                    sizeof(cs_subjects) / sizeof(Subject)};
  const Subject te_subjects[] = {
      {"Mobile and Wireless Communication"},
      {"Digital Signal Processing"},
      {"Antenna and Microwave Engineering"},
      {"Radar and Communication Systems"},
      {"Satellite Communication "},
      {"Network Security and Cryptography"},
  };
  const Discipline te_discipline = {"Telecommunications ", te_subjects,
                                    sizeof(te_subjects) / sizeof(Subject)};
  const Subject el_subjects[] = {
      {"Computer Architecture"},
      {"VLSI Design "},
      {"Microcontrollers and Microprocessors"},
      {"Analog Circut Design"},
      {"Power Electronics"},
      {"Embedded Systems "},
  };
  const Discipline el_discipline = {"Electronics ", el_subjects,
                                    sizeof(el_subjects) / sizeof(Subject)};
  const Subject ee_subjects[] = {
      {"Fundamentals of Electrical Engineering"},
      {"Circuit Theory"},
      {"Microcontrollers and Microprocessors"},
      {"Electrical Power Systems"},
      {"Power Electronics"},
      {"Embedded Systems "},
  };
  const Discipline ee_discipline = {"Electrical Engineering", ee_subjects,
                                    sizeof(ee_subjects) / sizeof(Subject)};

  const Discipline* current_discipline = NULL;
  if (!strcmp("cs", argv[1])) {
    current_discipline = &cs_discipline;
  } else if (!strcmp("ee", argv[1])) {
    current_discipline = &ee_discipline;
  } else if (!strcmp("te", argv[1])) {
    current_discipline = &te_discipline;
  } else if (!strcmp("el", argv[1])) {
    current_discipline = &el_discipline;
  } else {
    printf("Invalid discipline. %s\n", argv[1]);
    usage(argv[0]);

    return 1;
  }

  Student s1;
  s1.semsester = 3;
  const char* sname = "Brett Lee";
  s1.name = malloc(strlen(sname) + 1);
  if (s1.name == NULL) {
    perror("Malloc failed");
    return 1;
  }
  strncpy(s1.name, sname, strlen(sname));
  s1.name[strlen(sname)] = '\0';
  s1.discipline = current_discipline;
  // call the showSubjects function
  show_subjects(&s1);
  free(s1.name);
  s1.name = NULL;
  return 0;
}

void show_subjects(const Student* student) {
  printf("Name : %s\n", student->name);
  printf("Semester : %d\n", student->semsester);
  printf("Discipline: %s\n", student->discipline->discipline);
  printf("Subjects : \n");
  for (size_t i = 0; i < student->discipline->numSubjects; i++) {
    printf("\t %s\n", student->discipline->subjects[i].name);
  }
}
void usage(const char* programName) {
  printf("Usage : %s <discipline>\n", programName);
  printf("Available disciplines: \n");
  printf(
      "cs: Computer Science, ee: Electrical Engineering, el: Electronics, "
      "te: Telecommunications\n");
}