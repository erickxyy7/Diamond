#ifndef INTERPRETER_H
#define INTERPRETER_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "postfix.h"
#include "lang_obj.h"
#include "boolean.h"

#include "output/print_string_to_standard_output.h"
#include "output/print_number_to_standard_output.h"

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
      
      char *result = postfix_evaluator(data, expression, j);
      
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
      
      char *result = postfix_evaluator(data, expression, j);
      
      for(size_t i = 0; i < j; ++i)
        free(expression[i]);
      free(expression);
      
      if (is_number(result))
        print_number_to_standard_output(result);
      else if (is_string(result))
        print_string_to_standard_output(result);
      
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
      
      char *result = postfix_evaluator(data, expression, j);
      
      if (!is_true(result)) {
        int gauge = 0;
        while (true) {
          
          if (!strcmp(tokens[i], "while"))
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
    
    else if (!strcmp(tokens[i], "if")) {
      char **expression = NULL;
      
      size_t j = 0;
      while (strcmp(tokens[++i], ";")) {
        expression = realloc(expression, sizeof expression * j + 1);
        expression[j] = malloc(sizeof expression[j] * strlen(tokens[i]) + 1);
        strcpy(expression[j++], tokens[i]);
      }
      
      char *result = postfix_evaluator(data, expression, j);
      
      if (!is_true(result)) {
        int gauge = 0;
        while (true) {
          
          if (!strcmp(tokens[i], "if"))
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
    
    else if (!strcmp(tokens[i], "end")) {
      
      /* Finds the keyword this `end` is for. */
      int gauge = 0;
      int j = i - 1;
      
      while (true) {
        
        if (!strcmp(tokens[j], "end"))
          ++gauge;
        
        else if (!strcmp(tokens[j], "if")) {
          if (gauge == 0) {
            ++i;
            break;
          }
          
          --gauge;
        }
        
        else if (!strcmp(tokens[j], "while")) {
          if (gauge == 0) {
            i = --j;
            break;
          }
          
          --gauge;
        }
        
        --j;
      }
      
    }
  }
}

#endif /* interpreter.h */
