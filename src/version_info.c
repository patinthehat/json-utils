
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
#include "utils_json.h"

typedef struct version_info_s {
  int major;
  int minor;
  int patch;
  char * prerelease;
  char * metadata;
} version_info;


version_info * new_version_info()
{
  version_info * vi;
  vi = malloc(sizeof(vi));
  zero_fill((void**)&vi, sizeof(vi));
  vi->prerelease = malloc(64);
  vi->metadata   = malloc(64);
  memset(vi->prerelease, 0, 64);
  memset(vi->metadata, 0, 64);

  return vi;
}

void free_version_info(version_info ** vip)
{
  version_info * vi;
  vi = *vip;
  if (vi) {
    free(vi->metadata);
    free(vi->prerelease);
    free(*vip);
  }
}

void debug_version_info(version_info * vi)
{
  printf("\
struct version_info* {\n\
    major = %d;\n\
    minor = %d;\n\
    patch = %d;\n\
}\n\
\
", vi->major, vi->minor, vi->patch);
}

void version_info_increment(version_info * vi, char * field, int incrementBy)
{
  if (strcmp(field, "patch")==0) {
    vi->patch = vi->patch + incrementBy;
    if (vi->patch >= 100)
      field = "minor";
  }

  if (strcmp(field, "minor")==0) {
    vi->minor = vi->minor + incrementBy;
    if (vi->minor >= 100)
      field = "major";
    vi->patch = 0;
  }

  if (strcmp(field, "major")==0) {
    vi->major = vi->major + incrementBy;
    vi->minor = 0;
    vi->patch = 0;
  }

  if (vi->major < 0)
    vi->major = 0;

  if (vi->minor < 0)
    vi->minor = 0;

  if (vi->patch < 0)
    vi->patch = 0;
}


void version_info_load_field(version_info * vi, json_object**jobj, char * fieldName, int * field)
{
  json_object* jlast;
  if (json_object_has_item(*jobj, fieldName)) {
    jlast = get_object_item(*jobj, fieldName);
    *field = atoi(json_object_get_string(jlast));
    if (*field < 0)
      *field = 0;
  }
}

void version_info_load_field_str(version_info * vi, json_object**jobj, char * fieldName, char ** field)
{
  json_object* jlast;
  if (json_object_has_item(*jobj, fieldName)) {
    jlast = get_object_item(*jobj, fieldName);
    *field = json_object_get_string(jlast);

  }
}

void version_info_load_major(version_info * vi, json_object**jobj)
{
  version_info_load_field(vi, jobj, "major", &vi->major);
}

void version_info_load_minor(version_info * vi, json_object**jobj)
{
  version_info_load_field(vi, jobj, "minor", &vi->minor);
  /*
  json_object* jlast;
  if (json_object_has_item(*jobj, "minor")) {
    jlast = get_object_item(*jobj, "minor");
    vi->minor = atoi(json_object_get_string(jlast));
    if (vi->minor < 0)
      vi->minor = 0;
  }*/
}

void version_info_load_patch(version_info * vi, json_object**jobj)
{
  version_info_load_field(vi, jobj, "patch", &vi->patch);
}

