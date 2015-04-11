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
#include "util_files.h"

void show_usage(const char* appName, int exitApp, int exitCode) {
  char* usageStr;
  usageStr = malloc(strlen(appName)+64);
  sprintf(usageStr, "Usage: %s [filename] [field] [new value]", appName);
  show_message(usageStr, FALSE, 0);
  free(usageStr);
  if (exitApp)
    exit(exitCode);
}

int main (int argc, char *argv[]) {
 //char * string = "{'sitename' : 'joys of programming', 'tags' : [ 'c' , 'c++', 'java', 'PHP' ], 'details': { 'name' : 'Joys of Programming', 'Number of Posts' : 10 } }";
// json_object * jobj = json_tokener_parse(string);
  //int fd;

  if (argc < 4 || argc < 3 || argc < 2 || argc < 1) {
    show_usage(argv[0], TRUE, -1);
  }

  if (file_exists(argv[1]) != 1) {
    show_message("File not found.", TRUE, -2);
  }

  char* filename  = argv[1];
  char* fieldname = argv[2];
  const char* cfilename   = argv[1];
  const char* cfieldname  = argv[2];
  const char* newvalue    = argv[3];

  json_object* jobj = json_object_from_file(cfilename);
  json_object* jo   = json_object_new_string(newvalue);

  //enum json_type type;
  //s = malloc(128);
  //memcpy(s, sprintf("%s:%s",argv[2],argv[3]), 128);

  json_object_object_add(jobj, cfieldname, jo);
      
  printf("json=%s\n", json_object_to_json_string(jobj));

  json_object_object_foreach(jobj, key, val) {
    if (strcmp(key, argv[2])==0) {
      //printf("value: %s = %s\n", (key), json_object_to_json_string(val));
      printf("%s", json_object_get_string(val));
      /*
      printf("type: ");
      type = json_object_get_type(val);

      switch (type) {
        case json_type_null:
          printf("json_type_null\n");
          break;

        case json_type_boolean:
          printf("json_type_boolean\n");
          break;
        case json_type_double:
          printf("json_type_double\n");
          break;
        case json_type_int:
          printf("json_type_int\n");
          break;
        case json_type_object:
          printf("json_type_object\n");
          break;
        case json_type_array:
          printf("json_type_array\n");
          break;
        case json_type_string:
          printf("json_type_string\n");
          break;
     }*/
    }
  } //-- end foreach --//
  
  //printf("json=%s\n", json_object_to_json_string(jo));
  exit(0);
}

