#ifndef POSTFIX_H
#define POSTFIX_H 1

#include "token_checking.h"
#include "identifier_to_literal_value.h"
#include "operands.h"

char *postfix_evaluator(Data *data, char **expression, size_t expression_length) {
  
  Operands *operands = malloc(sizeof *operands);
  operands->top = NULL;
  
  identifier_to_literal_value(data, expression, expression_length);
  
  for(size_t i = 0; i < expression_length; ++i) {
    if (!strcmp(expression[i], "+") ||
        !strcmp(expression[i], "-") ||
        !strcmp(expression[i], "*") ||
        !strcmp(expression[i], "/") ||
        !strcmp(expression[i], "==")) {
      Operand *second_operand = pop__Operands(operands);
      Operand *first_operand = pop__Operands(operands);
      
      if (is_number(first_operand->value) && is_number(second_operand->value)) {
        double numeric_result;
        if (!strcmp(expression[i], "+"))
          numeric_result = atof(first_operand->value) + atof(second_operand->value);
        else if (!strcmp(expression[i], "-"))
          numeric_result = atof(first_operand->value) - atof(second_operand->value);
        else if (!strcmp(expression[i], "*"))
          numeric_result = atof(first_operand->value) * atof(second_operand->value);
        else if (!strcmp(expression[i], "/"))
          numeric_result = atof(first_operand->value) / atof(second_operand->value);
        else if (!strcmp(expression[i], "=="))
          numeric_result = atof(first_operand->value) == atof(second_operand->value);
        
        char *result = malloc(sizeof *result * total_digits(numeric_result) + 8);
        sprintf(result, "%.6lf", numeric_result);
        
        push__Operands(operands, result);
        
        free(result);
      } else if (is_string(first_operand->value) && is_string(second_operand->value)) {
        
        /**
         * Concatenates one string into another.
         */
        
        size_t result_length = sizeof(char) * strlen(first_operand->value) + strlen(second_operand->value) - 1;
        char *result = malloc(result_length);
        
        size_t i, j;
        for(i = 0; i < strlen(first_operand->value) - 1; ++i)
          result[i] = first_operand->value[i];
        for(j = 1; j < strlen(second_operand->value); ++j)
          result[i++] = second_operand->value[j];
        
        push__Operands(operands, result);
        
        free(result);
      }
      
      free(first_operand->value);
      free(first_operand);
      free(second_operand->value);
      free(second_operand);
    } else
      push__Operands(operands, expression[i]);
  }
  
  char *result = malloc(sizeof *result * strlen(operands->top->value) + 1);
  strcpy(result, operands->top->value);
  
  free(operands->top->value);
  free(operands->top);
  free(operands);
  
  return result;
}

#endif /* postfix.h */
