#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <limits.h>



// TODO: Add more fields to this struct
struct job {
    int id;
    int arrival;
    int length;
    int tickets;
    struct job *next;
};

/*** Globals ***/ 
int seed = 100;

//This is the start of our linked list of jobs, i.e., the job list
struct job *head = NULL;

/*** Globals End ***/

/*Function to append a new job to the list*/
void append(int id, int arrival, int length, int tickets){
  // create a new struct and initialize it with the input data
  struct job *tmp = (struct job*) malloc(sizeof(struct job));

  //tmp->id = numofjobs++;
  tmp->id = id;
  tmp->length = length;
  tmp->arrival = arrival;
  tmp->tickets = tickets;

  // the new job is the last job
  tmp->next = NULL;

  // Case: job is first to be added, linked list is empty 
  if (head == NULL){
    head = tmp;
    return;
  }

  struct job *prev = head;

  //Find end of list 
  while (prev->next != NULL){
    prev = prev->next;
  }

  //Add job to end of list 
  prev->next = tmp;
  return;
}


/*Function to read in the workload file and create job list*/
void read_workload_file(char* filename) {
  int id = 0;
  FILE *fp;
  size_t len = 0;
  ssize_t read;
  char *line = NULL,
       *arrival = NULL, 
       *length = NULL;
  int tickets = 0;

  struct job **head_ptr = malloc(sizeof(struct job*));

  if( (fp = fopen(filename, "r")) == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) > 1) {
    arrival = strtok(line, ",\n");
    length = strtok(NULL, ",\n");
    tickets += 100;
       
    // Make sure neither arrival nor length are null. 
    assert(arrival != NULL && length != NULL);
        
    append(id++, atoi(arrival), atoi(length), tickets);
  }

  fclose(fp);

  // Make sure we read in at least one job
  assert(id > 0);

  return;
}

/*---------------------------------------------------*/
void policy_STCF(struct job* head, int slice) {
  // TO DO FIXN THIS 
    struct job* current = head;
    struct job* next_job = NULL;
    int time = 0;

    while (current != NULL) {
        // Find the job with the shortest remaining time
        next_job = head;
        while (next_job != NULL) {
            if (next_job->arrival <= time) {
                if (next_job->length < current->length) {
                    current = next_job;
                }
            }
            next_job = next_job->next;
        }

        // Execute the current job for 'slice' time units
        if (current->length > slice) {
            current->length -= slice;
            time += slice;
        } else {
            time += current->length;
            current->length = 0;
        }

        // Move to the next time unit
        current = current->next;
    }
}
void analyze_STCF(struct job *head) {
  // TODO: Fill this in

  return;
}

/*---------------------------------------------------*/

void policy_RR(struct job* head, int slice) {
    struct job* current = head;
    int time = 0;

    while (current != NULL) {
        // Execute the current job for 'slice' time units
        if (current->length > slice) {
            current->length -= slice;
            time += slice;
        } else {
            time += current->length;
            current->length = 0;
        }

        // Move to the next job in a round-robin fashion
        current = current->next;
        if (current == NULL) {
            current = head;
        }
    }
}

void analyze_RR(struct job *head) {
  // TODO: Fill this in

  return;
}

/*------------------------------------------------------*/

void policy_LT(struct job *head, int slice) {
  // TODO: Fill this in

  return;
}

void analyze_LT(struct job *head) {
  // TODO: Fill this in

  return;
}

int main(int argc, char **argv) {

 if (argc < 5) {
    fprintf(stderr, "missing variables\n");
    fprintf(stderr, "usage: %s analysis-flag policy workload-file slice-length\n", argv[0]);
		exit(EXIT_FAILURE);
  }

  int analysis = atoi(argv[1]);
  char *policy = argv[2],
       *workload = argv[3];
  int slice = atoi(argv[4]);

  // Note: we use a global variable to point to 
  // the start of a linked-list of jobs, i.e., the job list 
  read_workload_file(workload);

  if (strcmp(policy, "STCF") == 0 ) {
    policy_STCF(head, slice);
    if (analysis) {
      printf("Begin analyzing STCF:\n");
      analyze_STCF(head);
      printf("End analyzing STCF.\n");
    }

    exit(EXIT_SUCCESS);
  }

  // TODO: Add other policies

  if (strcmp(policy, "RR") == 0 ) {
    policy_STCF(head, slice);
    if (analysis) {
      printf("Begin analyzing RR:\n");
      analyze_STCF(head);
      printf("End analyzing RR.\n");
    }

    exit(EXIT_SUCCESS);
  }

  if (strcmp(policy, "LT") == 0 ) {
    policy_STCF(head, slice);
    if (analysis) {
      printf("Begin analyzing LT:\n");
      analyze_STCF(head);
      printf("End analyzing LT.\n");
    }

    exit(EXIT_SUCCESS);
  } 

	exit(EXIT_SUCCESS);
}
