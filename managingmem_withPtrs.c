/**
 * This file simulates a possible real world scenario. The point of this C
 *program is Wired Brain Coffee has hired you to help fix their code so that
 *they manage memory more efficiently with less bugs. In the code below, there
 *is a memory leak being created in the form of a dangling pointer.
 *
 * Your mission is to identify and fix the memory leak that is occurring due to
 *one of the 'Wired Brain Coffee' API functions below.
 *
 * NOTE: In a real-world C library/program, there would be a header file
 *associated with this C file in order to better define a usable, public
 *API/interface and to separate declarations from instantiations. Function and
 *structure definitions are only included in this C file in order to condense
 *the number of files needed in order to follow along with this course so as to
 *reducing context switching.
 **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Globals
 **/
int metric_count = 0;

/**
 * Function/Structure Declarations
 **/

// Define a simple Metric type for sending off the amount of power used by the
// CoffeeMachine for a given sequence
typedef struct Metric {
  int sequence_number;
  float power_used;
} Metric;

// Define our CoffeeMachine type!
typedef struct CoffeeMachine {
  int (*pour)(int, struct CoffeeMachine*);
  Metric** metrics;
  int pour_duration;
} CoffeeMachine;

// CoffeeMachine Create/Destroy API
int init_coffee_machine(CoffeeMachine**);
void cleanup_machine(CoffeeMachine*);

// Different PourHandler Function Declarations
int pour_decaf(int, CoffeeMachine*);
int pour_classic(int, CoffeeMachine*);
int pour_rich(int, CoffeeMachine*);

// Metric API
Metric* create_metric(float);
int send_metrics(Metric**, size_t metric_size);

// This 'main' function is here to simply test and make use of the API functions
// below
int main(int argc, char* argv[]) {
  // Instantiate a test coffee machine
  CoffeeMachine* my_machine;
  if (init_coffee_machine(&my_machine)) {
    printf(
        "System does not have enough memory to allocate a CoffeeMachine "
        "structure\n");
    return 1;
  }

  printf("\nMachine Activated\n");

  char* user_pour_mode = argv[1];
  int duration = strtol(argv[2], NULL, 10);

  my_machine->pour_duration = duration;

  // A pour mode (one of 'decaf', 'rich', or 'classic') is required along with a
  // pour duration.
  if (argc > 2) {
    // Set the 'pour' function pointer based on the pour mode argument
    if (!strcmp("decaf", user_pour_mode)) {
      my_machine->pour = pour_decaf;
    } else if (!strcmp("rich", user_pour_mode)) {
      my_machine->pour = pour_rich;
    } else {
      my_machine->pour = pour_classic;
    }
  } else {
    printf("Please pass pour mode and pour duration arguments!");
    return 1;
  }

  printf("\nBeginning Pour With Duration: %d\n", duration);

  my_machine->pour(duration, my_machine);

  printf("\nPour Complete. Sending Metrics...\n");
  send_metrics(my_machine->metrics, duration);

  printf("\nPerforming Cleanup...\n");
  cleanup_machine(my_machine);

  return 0;
}

/**
 * Wired Brain Coffee API Functions
 **/

// Dynamically allocates enough memory for a CoffeeMachine type
int init_coffee_machine(CoffeeMachine** machine) {
  if ((*machine = (CoffeeMachine*)malloc(sizeof(CoffeeMachine)))) {
    return 0;
  } else {
    return 1;
  }
}

// Pours a decaf cup of coffee
int pour_decaf(int duration, CoffeeMachine* machine) {
  int start = 0;
  Metric** metrics_ptr = (Metric**)malloc(duration * sizeof(Metric));
  machine->metrics = metrics_ptr;

  while (start < duration) {
    // Do some processing of pouring here....
    float power_used = 4.4;

    Metric* metric = create_metric(power_used);
    *(metrics_ptr + start) = metric;

    start++;
  }

  return 0;
}
/*
In the context of the coffee pouring simulation, the `duration` argument
specifies how long the coffee pouring process will take. During this process,
the coffee machine generates metrics at specific time intervals to measure the
power used. Since the `duration` can vary depending on how long the user decides
to pour the coffee, the number of metrics that need to be generated is not
predetermined at compile-time. Instead, it's determined dynamically based on the
user's input.

For example, let's say the user specifies a `duration` of 10 seconds for pouring
coffee. During this 10-second duration, the coffee machine generates metrics,
let's say every 1 second, to track the power usage. This means that in this
case, you would need to generate 10 metrics (one for each second).

On the other hand, if the user specifies a `duration` of 20 seconds, you would
need to generate 20 metrics (one for each second). The number of metrics
directly depends on the `duration` value, and it's not something that can be
hardcoded because it's determined by user input at runtime.

To accommodate this dynamic and runtime-dependent nature of metric generation,
dynamic memory allocation is used. When the `duration` is known, the `pour`
function dynamically allocates memory for an array of pointers to `Metric`
structs, where each pointer represents a metric generated at a specific time
interval during the pour operation. This allows each metric to be stored
independently and associated with a specific point in time during the pour
process.

In summary, the need for dynamic memory allocation arises from the fact that the
number of metrics to be generated is determined at runtime based on the
`duration` provided by the user. This dynamic nature requires the creation of an
array of pointers to `Metric` structs, and that's why dynamic memory allocation
is used in this scenario.
*/
// Pours a classic cup of coffee
/*
The pour_classic function takes two parameters: duration, which specifies the
pouring time, and machine, a pointer to the CoffeeMachine structure.

Inside the function, an integer start is initialized to 0. This variable will be
used to keep track of the pouring process's progress.

A double pointer Metric **metrics_ptr is declared. This pointer will store the
address of the dynamically allocated array of pointers to Metric structs. The
size of this array is calculated as duration * sizeof(Metric), as there will be
one metric for each unit of time during the pour.

The metrics_ptr array is assigned to the machine->metrics member of the
CoffeeMachine structure. This way, the metrics_ptr array will be accessible from
outside the function.

A while loop is used to generate metrics for the specified duration. The loop
iterates duration times, each time representing a unit of time during the pour.

Inside the loop, a local variable power_used is set to 5.6. This simulates the
power consumption during the coffee pouring process.

The create_metric function is called with the power_used value to create a new
Metric struct. The returned Metric pointer is assigned to the current element in
the metrics_ptr array, which corresponds to the current unit of time during
pouring.

The start variable is incremented to move to the next time interval.

Once the loop completes, the function returns 0 to indicate successful
completion.

In summary, the pour_classic function dynamically allocates memory for an array
of pointers to Metric structs, associates this array with the metrics member of
the CoffeeMachine structure, and then populates this array with Metric structs,
each representing power usage during a specific unit of time during the coffee
pouring process. This approach allows for flexible memory allocation and
tracking of metrics based on the dynamic duration of the pour.
*/
int pour_classic(int duration, CoffeeMachine* machine) {
  int start = 0;
  Metric** metrics_ptr = (Metric**)malloc(duration * sizeof(Metric));
  machine->metrics = metrics_ptr;

  while (start < duration) {
    // Do some processing of pouring here....
    float power_used = 5.6;

    Metric* metric = create_metric(power_used);
    *(metrics_ptr + start) = metric;
    start++;
  }

  return 0;
}

// Pours a rich cup of coffee
int pour_rich(int duration, CoffeeMachine* machine) {
  int start = 0;
  Metric** metrics_ptr = (Metric**)malloc(duration * sizeof(Metric));
  machine->metrics = metrics_ptr;

  while (start < duration) {
    // Do some processing of pouring here....
    float power_used = 3.7;
    Metric* metric = create_metric(power_used);
    *(metrics_ptr + start) = metric;

    start++;
  }

  return 0;
}

// Dynamically allocates memory for a new Metric while coffee is being poured
Metric* create_metric(float power_used) {
  Metric* metric = (Metric*)malloc(sizeof(Metric));
  metric->sequence_number = ++metric_count;
  metric->power_used = power_used;

  return metric;
}

// Sends a dynamically allocated array of Metrics to an external API
int send_metrics(Metric** metrics, size_t metric_count) {
  if (metrics == NULL) {
    return 1;
  }

  for (int i = 0; i < metric_count; i++) {
    // Metric *metric = metrics[i];
    printf("\nMetric Count: %d\n",
           metrics[i]->sequence_number /*metric->sequence_number;*/);
    printf("Metric Power Used: %f\n", metrics[i]->power_used);
    // Here we could send each metric to the cloud via an external service.
  }

  return 0;
}

// Frees up resources that were allocated in relation to a CoffeeMachine
void cleanup_machine(CoffeeMachine* machine) {
  /*for(int i = 0; i < machine->pour_duration; i++) {
          Metric *metric = machine->metrics[i];
          printf("\nFreeing Metric At Count: %d\n", metric->sequence_number);
          free(metric);
      }

      free(machine->metrics);
  */
  if (machine) {
    if (machine->metrics) {
      for (int i = 0; i < machine->pour_duration; i++) {
        free(machine->metrics[i]);
      }
      free(machine->metrics);
    }
    free(machine);
  }
}
