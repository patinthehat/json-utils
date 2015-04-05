
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "consts.h"
#include "utils.h"


/**
 * Checks if a file exists or not.
 * uses stat(), which is slightly faster
 * @return int Returns 1 if the file exists, otherwise 0
 */
int file_exists(char *filename)
{
  struct stat buffer;
  if (stat(filename, &buffer) == 0)
    return 1;
  return 0;
}



void file_write_data(char * filename, const char * data)
{
  FILE * fp;
  fp = fopen(filename, "w");
  if (fp == NULL)
    show_message("Failed to open file for writing.", TRUE, -3);
  fprintf(fp, "%s", data);
  fclose(fp);
}


void file_touch(char * filename)
{
  int fd;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  fd = creat(filename, mode);
  close(fd);
}
