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

#include "consts.h"

#include "utils.h"
#include "util_files.h"
#include "utils_json.h"
#include "version_info.h"

#define JSONSEMVER_VERSION = "1.2.0"

typedef struct app_settings_s {
  int incrementBy;
  char * fieldName;
} app_settings;



char * str_new(char ** str, int size, int zeroFill)
{
  *str = malloc(size);
  if (zeroFill == 1)
    memset(*str, 0, size);
  return *str;
}

void string_free(char ** str)
{
  if (*str)
    free(*str);
}

void str_set(char ** str, char * strCopy)
{
  sprintf(*str, "%s", strCopy);
}

char * str_new_set(char ** str, int size, char * strCopy)
{
  char * s = str_new(str, size, 1);
  str_set(str, strCopy);
  return s;
}

int main (int argc, char *argv[])
{
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;
  char * cfn;
  char * fieldToIncrement;
  const char* cfilename   = argv[1];
  int index;
  int c;

  version_info vi;
  version_info * vip = &vi;

  json_object* jobj = json_object_from_file(cfilename);
  json_object * joPatch;
  json_object * joMinor;
  json_object * joMajor;

//-------------------------

  str_new_set(&cfn, 4096, argv[1]);
  str_new(&fieldToIncrement, 16, 1);

  zero_fill((void**)&vip, sizeof(vi));

  version_info_load_major(&vi, &jobj);
  version_info_load_minor(&vi, &jobj);
  version_info_load_patch(&vi, &jobj);

  if (argc >= 3) {
    str_set(&fieldToIncrement, argv[2]);
  }

  if (argc == 2) {
    str_set(&fieldToIncrement, "patch");
  }

  version_info_increment(&vi, fieldToIncrement, 1);

  joPatch = json_object_new_int(vi.patch);
  joMinor = json_object_new_int(vi.minor);
  joMajor = json_object_new_int(vi.major);

  json_object_object_add(jobj, "patch", joPatch);
  json_object_object_add(jobj, "minor", joMinor);
  json_object_object_add(jobj, "major", joMajor);

  file_write_data(cfn, json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PLAIN));

  debug_version_info(&vi);

  string_free(&fieldToIncrement);
  string_free(&cfn);

  return 0;

  opterr = 0;
  while ((c = getopt (argc, argv, "abf:")) != -1)
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
