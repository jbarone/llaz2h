#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv) {
  printf("Usage: %s -n -f <database file>\n", argv);
  printf("\t%s\n", "-n - create new database file");
  printf("\t%s\n", "-f - (required) path to the database file");
  return;
}

int main(int argc, char *argv[]) {
  int c;
  bool newfile = false;
  char *filepath = NULL;

  int dbfd = -1;
  struct dbheader_t *dbhdr = NULL;

  while ((c = getopt(argc, argv, "nf:")) != -1) {
    switch (c) {
    case 'n':
      newfile = true;
      break;
    case 'f':
      filepath = optarg;
      break;
    case '?':
      printf("Unknown option -%c\n", optopt);
      break;
    default:
      return -1;
    }
  }

  if (filepath == NULL) {
    printf("%s\n", "Filepath is a required argument");
    print_usage(argv[0]);
    return 0;
  }

  if (newfile) {
    dbfd = create_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      printf("%s\n", "Failed to create new database file");
      return -1;
    }

    if (create_db_header(dbfd, &dbhdr) == STATUS_ERROR) {
      printf("%s\n", "Failed to create database header");
      close(dbfd);
      return -1;
    }
  } else {
    dbfd = open_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      printf("%s\n", "Failed to open database file");
      return -1;
    }

    if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR) {
      printf("%s\n", "Invalid database header");
      close(dbfd);
      return -1;
    }
  }

  printf("Newfile: %d\n", newfile);
  printf("Filepath: %s\n", filepath);

  output_file(dbfd, dbhdr, NULL);

  return 0;
}
