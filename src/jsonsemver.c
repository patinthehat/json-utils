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
#include <getopt.h>

#include "utils.h"



typedef struct version_info_s {
  int major;
  int minor;
  int patch;
  char * prerelease;
  char * metadata;
} version_info;

typedef struct app_settings_s {
  int incrementBy;
  char * fieldName;
} app_settings;


void debug_version_info(version_info * vi)
{
  printf("struct version_info {\n\t major = %d;\n\t minor = %d;\n\t patch = %d;\n}\n", vi->major, vi->minor, vi->patch);
}


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


int main (int argc, char *argv[])
{
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;
  const char* cfilename   = argv[1];
  char * cfn;// = cfilename;
  int index;
  int c;


  cfn = malloc(4096);
  memset(cfn, 0, 4096);

  sprintf(cfn, "%s", argv[1]);

  json_object* jobj       = json_object_from_file(cfilename);
  json_object* jlast;
  version_info vi;

  memset(&vi, 0, sizeof(vi));

  if (json_object_has_item(jobj, "major")) {
    jlast = get_object_item(jobj, "major");
    vi.major = atoi(json_object_get_string(jlast));
    if (vi.major < 0)
      vi.major = 0;
  }

  if (json_object_has_item(jobj, "minor")) {
    jlast = get_object_item(jobj, "minor");
    vi.minor = atoi(json_object_get_string(jlast));
    if (vi.minor < 0)
      vi.minor = 0;
  }

  if (json_object_has_item(jobj, "patch")) {
    jlast = get_object_item(jobj, "patch");
    vi.patch = atoi(json_object_get_string(jlast));
    if (vi.patch < 0)
      vi.patch = 0;
  }

  json_object * joPatch;
  json_object * joMinor;
  json_object * joMajor;
  char * fieldToIncrement;

  fieldToIncrement = malloc(16);
  memset(fieldToIncrement, 0, 16);

  if (argc >= 3) {
    sprintf(fieldToIncrement, "%s", argv[2]);
    //fieldToIncrement = argv[2];
  }

  if (argc == 2) {
    sprintf(fieldToIncrement, "%s", "patch");
  }

  version_info_increment(&vi, fieldToIncrement, 1);

  joPatch = json_object_new_int(vi.patch);
  joMinor = json_object_new_int(vi.minor);
  joMajor = json_object_new_int(vi.major);

  json_object_object_add(jobj, "patch", joPatch);
  json_object_object_add(jobj, "minor", joMinor);
  json_object_object_add(jobj, "major", joMajor);

  write_data_to_file(cfn, json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PLAIN));

  debug_version_info(&vi);

  free(fieldToIncrement);
  free(cfn);

  return 0;

  opterr = 0;
  while ((c = getopt (argc, argv, "abc:")) != -1)
    switch (c)
      {
      case 'a':
        aflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'f':
        cvalue = optarg;
        break;
      case '?':
        if (optopt == 'f')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  printf ("aflag = %d, bflag = %d, cvalue = %s\n",
          aflag, bflag, cvalue);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}
