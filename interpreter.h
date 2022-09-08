#ifndef INTERPRETER_H
#define INTERPRETER_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "postfix.h"
#include "lang_obj.h"

void interpreter(char **tokens, size_t tokens_length) {
  
  Data *data = malloc(sizeof *data);
  initialize__Data(data);
  
  for(size_t i = 0; i < tokens_length; ++i) {
    
    if (!strcmp(tokens[i], "=")) {
      
      size_t name = i - 1;
      
      char **expression = NULL;
      
      size_t j = 0;
      while (strcmp(tokens[++i], ";")) {
        
        expression = realloc(expression, sizeof expression * j + 1);
        expression[j] = malloc(sizeof expression[j] * strlen(tokens[i]) + 1);
        
        strcpy(expression[j++], tokens[i]);
        
      }
      
      char *result = postfix_evaluator(expression, j);
      
      Lang_obj *lang_obj = name_exists(data, tokens[name]);
      
      if (!lang_obj) {
        lang_obj = create_Lang_obj(tokens[name], result);
        push__Data(data, lang_obj);
      } else {
        lang_obj->value = realloc(lang_obj->value, sizeof (char) * strlen(result) + 1);
        strcpy(lang_obj->value, result);
      }
      
      free(result);
      
      for(size_t i = 0; i < j; ++i)
        free(expression[i]);
      free(expression);
    }
    
    else if (!strcmp(tokens[i], "puts")) {
      
      char **expression = NULL;
      
      size_t j = 0;
      while (strcmp(tokens[++i], ";")) {
        
        expression = realloc(expression, sizeof expression * j + 1);
        expression[j] = malloc(sizeof expression[j] * strlen(tokens[i]) + 1);
        
        strcpy(expression[j++], tokens[i]);
        
      }
      
      char *result = postfix_evaluator(expression, j);
      
      for(size_t i = 0; i < j; ++i)
        free(expression[i]);
      free(expression);
      
      puts(result);
      
      free(result);
    }
    
    else if (!strcmp(tokens[i], "while")) {
      
      char **expression = NULL;
      
      size_t j = 0;
      while (strcmp(tokens[++i], ";")) {
        expression = realloc(expression, sizeof expression * j + 1);
        expression[j] = malloc(sizeof expression[j] * strlen(tokens[i]) + 1);
        strcpy(expression[j++], tokens[i]);
      }
      
      char *result = postfix_evaluator(expression, j);
      
      if (atof(result) == 0) {
        int gauge = 0;
        while (true) {
          
          if (!strcmp(tokens[i], "while") || !strcmp(tokens[i], "if"))
            ++gauge;
          else if (!strcmp(tokens[i], "end")) {
            if (gauge == 0) {
              ++i;
              break;
            }
            --gauge;
          }
          
          ++i;
        }
      }
      
      for(size_t i = 0; i < j; ++i)
        free(expression[i]);
      free(expression);
      free(result);
    }
  }
  
  /* Prints all program variables. */
  Lang_obj *lang_obj = pop__Data(data);
  while (lang_obj != NULL) {
    printf("%s: %s\n", lang_obj->name, lang_obj->value);
    lang_obj = pop__Data(data);
  }
}

#endif /* interpreter.h */
