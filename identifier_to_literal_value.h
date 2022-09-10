#ifndef IDENTIFIER_TO_LITERAL_VALUE_H
#define IDENTIFIER_TO_LITERAL_VALUE_H 1

#include "lang_obj.h"
#include "token_checking.h"

void identifier_to_literal_value(Data *data, char **expression, size_t expression_length) {
  
  for(size_t i = 0; i < expression_length; ++i) {
    if (is_identifier(expression[i])) {
      
      Lang_obj *lang_obj = data->top;
      while (lang_obj != NULL) {
        
        if (!strcmp(lang_obj->name, expression[i])) {
          expression[i] = realloc(expression[i], strlen(lang_obj->value) + 1);
          strcpy(expression[i], lang_obj->value);
        }
        
        lang_obj = lang_obj->previous_lang_obj;
      }
      
    }
  }
}

#endif /* identifier_to_literal_value.h */
