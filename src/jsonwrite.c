/**
 *
 * jsonwrite --
 *    writes data to a specified json file.
 *
 * usage:
 *    jsonwrite <filename> <fieldname, fieldname, ...> new-value
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
#include "utils_json.h"
#include "util_files.h"

void show_usage(const char* appName, int exitApp, int exitCode) {
  char* usageStr;
  usageStr = malloc(strlen(appName)+64);
  sprintf(usageStr, "Usage: %s [filename] [field, field, ...] [new-value]", appName);
  show_message(usageStr, FALSE, 0);
  free(usageStr);
  if (exitApp)
    exit(exitCode);
}

void file_write(char * filename, char * data)
{
  FILE* fp;
  fp = fopen(filename, "w+");
  if (fp == NULL)
    show_message("Failed to open file for writing.", TRUE, -3);

  fprintf(fp, "%s", data);
  fclose(fp);
}

int main (int argc, char *argv[]) {

  char * filename;

  if (argc < 4 || argc < 3 || argc < 2 || argc < 1)
    show_usage(argv[0], TRUE, -1);

  filename = argv[1];

  if (file_exists(filename) != 1) {
    file_write(filename, "{ }");
  }

  char * cNewValue = argv[argc-1];
  json_object * jobj  = json_object_from_file(filename);
  json_object * jobj2 = jobj;
  json_object * jLast;
  json_object * jobj3;

  int i;
  char *key;

  //skip the first argument and the last argument
  for(i = 2; i < argc-1; i++) {
    key = argv[i];
    jLast = jobj2;

    if (i == argc-2) {
      jobj3 = json_object_new_string(argv[argc-1]);
      json_object_get(jobj3);
      json_object_object_add(jLast, key, (jobj3));
      json_object_put(jobj3);
      break;
    }

    //this gets an existing field, if it exists, otherwise creates a new one.
    if (json_object_object_get_ex(jLast, key, &jobj2) != TRUE) {
      jobj2 = json_object_new_object();
    }

    json_object_object_add(jLast, key, json_object_get(jobj2));
  }

  json_object_to_file(filename, jobj);

  exit(0);
}

