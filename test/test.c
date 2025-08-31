#include "common.h"
#include <stdio.h>
#include <stdlib.h>

#define HEADER_MAGIC 0x4c4c4144
#define NAME_LEN 256
#define ADDRESS_LEN 256

struct employee_t {
  char name[NAME_LEN];
  char address[ADDRESS_LEN];
  unsigned int hours;
};

struct dbheader_t {
  unsigned int magic;
  unsigned short version;
  unsigned short count;
  unsigned int filesize;
};

int create_db_header(struct dbheader_t **headerOut);
int add_employee(struct dbheader_t *dbhdr, struct employee_t **employees,
                 char *addstring);

int main(int argc, char *argv[]) {
  struct dbheader_t *dbhdr = NULL;
  struct employee_t *employees = NULL;

  if (create_db_header(&dbhdr) == STATUS_ERROR) {
    printf("Failed to create database header\n");
    return -1;
  }

  printf("Database Header:\n");
  printf("Magic: 0x%X\n", dbhdr->magic);
  printf("Version: %d\n", dbhdr->version);
  printf("Count: %d\n", dbhdr->count);
  printf("Filesize: %d\n", dbhdr->filesize);
  printf("#####################################################################"
         "###########\n");

  if (add_employee(dbhdr, &employees, "John Doe,123 Main St,40") ==
      STATUS_ERROR) {
    printf("Failed to add employee\n");
    free(dbhdr);
    return -1;
  }

  printf("Database Header:\n");
  printf("Magic: 0x%X\n", dbhdr->magic);
  printf("Version: %d\n", dbhdr->version);
  printf("Count: %d\n", dbhdr->count);
  printf("Filesize: %d\n", dbhdr->filesize);
  printf("#####################################################################"
         "###########\n");

  printf("\nEmployees:\n");
  for (int i = 0; i < dbhdr->count; i++) {
    printf("Name: %s, Address: %s, Hours: %d\n", employees[i].name,
           employees[i].address, employees[i].hours);
  }

  free(dbhdr);
  free(employees);
  return 0;
}
