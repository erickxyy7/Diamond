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

void push__Data(Data *data, Lang_obj *obj) {
  obj->previous_lang_obj = data->top;
  data->top = obj;
}

Lang_obj *pop__Data(Data *data) {
  Lang_obj *lang_obj = data->top;
  
  if (!lang_obj)
    return lang_obj;
  
  data->top = data->top->previous_lang_obj;
  return lang_obj;
}

Lang_obj *create_Lang_obj(char *name, char *value) {
  Lang_obj *lang_obj = malloc(sizeof *lang_obj);
  
  size_t name_length = sizeof(char) * strlen(name) + 1;
  lang_obj->name = malloc(name_length);
  strcpy(lang_obj->name, name);
  
  size_t value_length = sizeof(char) * strlen(value) + 1;
  lang_obj->value = malloc(value_length);
  strcpy(lang_obj->value, value);
  
  return lang_obj;
}

/* Test if a name exists in `data` stack. */
Lang_obj *name_exists(Data *data, char *name) {
  Lang_obj *lang_obj = data->top;
  while (lang_obj) {
    
    if (!strcmp(lang_obj->name, name))
      return lang_obj;
    
    lang_obj = lang_obj->previous_lang_obj;
  }
  return NULL;
}

#endif /* lang_obj.h */
