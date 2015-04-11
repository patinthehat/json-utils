
#include <json-c/json.h>


#define UTILS_JSON_H 1

json_object* get_object_item(json_object* jo, char * name);
int json_object_has_item(json_object* jo, char* name);

int json_object_is_array(json_object* jo);
