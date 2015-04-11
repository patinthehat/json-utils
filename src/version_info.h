
typedef struct version_info_s {
  int major;
  int minor;
  int patch;
  char * prerelease;
  char * metadata;
} version_info;


version_info * new_version_info();
void free_version_info(version_info * vi);
void debug_version_info(version_info * vi);

void version_info_increment(version_info * vi, char * field, int incrementBy);

void version_info_load_field(version_info * vi, json_object**jobj, char * fieldName, int * field);
void version_info_load_field_str(version_info * vi, json_object**jobj, char * fieldName, char ** field);

void version_info_load_major(version_info * vi, json_object**jobj);
void version_info_load_minor(version_info * vi, json_object**jobj);
void version_info_load_patch(version_info * vi, json_object**jobj);
