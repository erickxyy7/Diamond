#ifndef LANG_OBJ
#define LANG_OBJ 1

typedef struct Lang_obj {
  char *name;
  char *value;
  struct Lang_obj *previous_lang_obj;
} Lang_obj;

/* A stack that stores every `Lang_obj`. */
typedef struct Data {
  Lang_obj *top;
} Data;

#endif /* lang_obj.h */
