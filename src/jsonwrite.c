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
  sprintf(usageStr, "Usage: %s [filename] [field] [new-value]", appName);
  show_message(usageStr, FALSE, 0);
  free(usageStr);
  if (exitApp)
    exit(exitCode);
}

int main (int argc, char *argv[]) {
  //char * string = "{'sitename' : 'joys of programming', 'tags' : [ 'c' , 'c++', 'java', 'PHP' ], 'details': { 'name' : 'Joys of Programming', 'Number of Posts' : 10 } }";
  // json_object * jobj = json_tokener_parse(string);

  if (argc < 4 || argc < 3 || argc < 2 || argc < 1)
    show_usage(argv[0], TRUE, -1);

  if (file_exists(argv[1]) != 1) {
    //show_message("File not found.", TRUE, -2);
    FILE* fp;
    fp = fopen(argv[1], "w+");
    if (fp == NULL)
      show_message("Failed to open file for writing.", TRUE, -3);

    fprintf(fp, "%s", "{ }");
    fclose(fp);

  }

  FILE * fp;
  const char * cNewValue = argv[3];
  json_object * jobj  = json_object_from_file(argv[1]);
  json_object * jo    = json_object_new_string(cNewValue);
  
  json_object_object_add(jobj, argv[2], jo);
  //json_object_object_foreach(jobj, key, val) { }
  
  fp = fopen(argv[1], "w");
  if (fp == NULL)
    show_message("Failed to open file for writing.", TRUE, -3);
  
  fprintf(fp, "%s", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PLAIN));
  fclose(fp);
  
  exit(0);
}

