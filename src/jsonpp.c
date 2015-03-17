/**
 *
 * jsonread --
 *    reads and outputs a field from a specified json file.
 *
 * usage:
 *    jsonread [filename] [fieldname]
 *
 */

#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <unistd.h>

#include "utils.h"

void show_usage(const char* appName, int exitApp, int exitCode) {
  char* usageStr;
  usageStr = malloc(strlen(appName)+64);
  sprintf(usageStr, "Usage: %s [filename]", appName);
  show_message(usageStr, FALSE, 0);
  free(usageStr);
  if (exitApp)
    exit(exitCode);
}

int main (int argc, char *argv[]) {

  if (argc < 2 || argc < 1)
    show_usage(argv[0], TRUE, -1);

  if (file_exists(argv[1]) != 1) {
    printf("File not found.\n");
    exit(-1);
  }

  json_object * jobj  = json_object_from_file(argv[1]);

  printf("%s\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PRETTY));

  exit(0);
}

