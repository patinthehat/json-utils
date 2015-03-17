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
  usageStr = malloc(strlen(appName)+32);
  sprintf(usageStr, "Usage: %s [filename] [field]", appName);
  show_message(usageStr, FALSE, 0);
  free(usageStr);
  if (exitApp)
    exit(exitCode);
}

int main (int argc, char *argv[]) {

  if (argc < 3 || argc < 2 || argc < 1) {
    show_usage(argv[0], TRUE, -1);
  }

  if (file_exists(argv[1]) != 1) {
    show_message("File not found.", TRUE, -2);
  }

  const char* cfilename   = argv[1];
  const char* cfieldname  = argv[2];
  json_object* jobj       = json_object_from_file(cfilename);

  json_object_object_foreach(jobj, key, val) {
    if (strcmp(key, cfieldname)==0) {
      printf("%s", json_object_get_string(val));
    }
  }
  
  exit(0);
}

