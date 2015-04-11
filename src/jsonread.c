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
#include <stdint.h>
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
#include "utils_json.h"

void show_usage(const char* appName, int exitApp, int exitCode) {
  char* usageStr;
  int usageStrSize = strlen(appName)+128;
  usageStr = malloc(usageStrSize);
  memset(usageStr, 0, usageStrSize);

  sprintf(usageStr, "Usage: %s [filename] [field1] <[sub-field-1], [sub-field-2], ...>", appName);
  show_message(usageStr, FALSE, 0);
  free(usageStr);
  if (exitApp)
    exit(exitCode);
}

int json_object_is_string(json_object* jo) {
  return (json_object_is_type(jo, json_type_string) ? TRUE : FALSE);
}

int json_object_is_boolean(json_object* jo) {
  return (json_object_is_type(jo, json_type_boolean) ? TRUE : FALSE);
}


//int json_object_is_array(json_object* jo) {
//  return (json_object_is_type(jo, json_type_array) ? TRUE : FALSE);
//}


int json_object_is_int(json_object* jo) {
  return (json_object_is_type(jo, json_type_int) ? TRUE : FALSE);
}

int json_object_is_object(json_object* jo) {
  return (json_object_is_type(jo, json_type_object) &&
          !json_object_is_array(jo) ? TRUE : FALSE);
}


/*json_object* get_object_item(json_object* jo, char * name)
{
  json_object_object_foreach(jo, key, val) {
    if (strcmp(key, name)==0) {
      return val;
    }
  }
  return FALSE;
}*/

/*int json_object_has_item(json_object* jo, char* name)
{
  json_object_object_foreach(jo, key, val) {
    if (strcmp(key, name)==0) {
      return TRUE;
    }
  }
  return FALSE;
}*/



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
  json_object* jlast;

  int i;
  jlast = jobj;
  for(i = 2; i < argc; i++) {
    //printf("arg %d = %s \n", i, argv[i]);

    //argument is referencing an array item by index
    if (json_object_is_array(jlast) && str_is_integer(argv[i])) {
      jlast = json_object_array_get_idx(jlast, atol(argv[i]));
      continue;
    }

    if (json_object_has_item(jlast, argv[i])) {
      jlast = get_object_item(jlast, argv[i]);
    } else {
      jlast = NULL;
    }
  }

  //item was not found
  if (jlast == NULL) {
    printf("%s", "");
    exit(1);
  }

  //print string value or JSON representation of the object
  printf("%s", json_object_get_string(jlast));

  exit(0);
}

