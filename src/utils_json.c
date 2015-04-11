
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


json_object* get_object_item(json_object* jo, char * name)
{
  json_object_object_foreach(jo, key, val) {
    if (strcmp(key, name)==0) {
      return val;
    }
  }
  return FALSE;
}

int json_object_has_item(json_object* jo, char* name)
{
  json_object_object_foreach(jo, key, val) {
    if (strcmp(key, name)==0) {
      return TRUE;
    }
  }
  return FALSE;
}


int json_object_is_array(json_object* jo) {
  return (json_object_is_type(jo, json_type_array) ? TRUE : FALSE);
}
