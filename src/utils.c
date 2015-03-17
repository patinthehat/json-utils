
#ifndef TRUE
  #define TRUE 1
#endif
#ifndef FALSE
  #define FALSE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include <fcntl.h>

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

void show_message(char* message, int exitApp, int exitCode ) {
  printf("%s\n", message);
  if (exitApp)
    exit(exitCode);
}


