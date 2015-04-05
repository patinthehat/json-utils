
#include "consts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#include <fcntl.h>


void show_message(char* message, int exitApp, int exitCode ) {
  printf("%s\n", message);
  if (exitApp)
    exit(exitCode);
}

int str_is_integer(char * input)
{
  while (*input) {
    if (!isdigit(*input))
      return FALSE;
    input++;
  }
  return TRUE;
}

void zero_fill(void ** ptr, int size)
{
  memset(*ptr, 0, size);
}
