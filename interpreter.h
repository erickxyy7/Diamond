#ifndef INTERPRETER_H
#define INTERPRETER_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix.h"
#include "lang_obj.h"

void interpreter(char **tokens, size_t tokens_length) {
  
  Data *data = malloc(sizeof *data);
  data->top = NULL;
  
  for(size_t i = 0; i < tokens_length; ++i) {
    
    if (!strcmp(tokens[i], "=")) {
      
      char **expression = NULL; // <- free it.
      
      size_t j = 0;
      while (strcmp(tokens[++i], ";")) {
        
        expression = realloc(expression, sizeof expression * j + 1);
        expression[j] = malloc(sizeof expression[j] * strlen(tokens[i]) + 1);
        
        strcpy(expression[j++], tokens[i]);
        
      }
      
      char *result = postfix_evaluator(expression, j);
      puts(result);
      free(result);
      
      for(size_t i = 0; i < j; ++i)
        free(expression[i]);
      free(expression);
    }
  }
  
}

#endif /* interpreter.h */
