#ifndef POSTFIX_H
#define POSTFIX_H 1

#include "token_checking.h"

size_t total_digits(int n) {
  if (n < 0) {
    if (n > -10) return 2;
    if (n > -100) return 3;
    if (n > -1000) return 4;
    if (n > -10000) return 5;
    if (n > -100000) return 6;
    if (n > -1000000) return 7;
    if (n > -10000000) return 8;
    if (n > -100000000) return 9;
    if (n > -1000000000) return 10;
    if (n > -10000000000) return 11;
  }
  
  if (n < 10) return 1;
  if (n < 100) return 2;
  if (n < 1000) return 3;
  if (n < 10000) return 4;
  if (n < 100000) return 5;
  if (n < 1000000) return 6;
  if (n < 10000000) return 7;
  if (n < 100000000) return 8;
  if (n < 1000000000) return 9;
  if (n < 10000000000) return 10;
}

typedef struct Operand {
  char *value;
  struct Operand *previous_operand;
} Operand;

typedef struct Operands {
  Operand *top;
} Operands;

void push__Operands(Operands *operands, char *value) {
  Operand *operand = malloc(sizeof *operand);
  operand->value = malloc(sizeof operand->value * strlen(value) + 1);
  strcpy(operand->value, value);
  operand->previous_operand = operands->top;
  operands->top = operand;
}

Operand *pop__Operands(Operands *operands) {
  Operand *operand = operands->top;
  operands->top = operands->top->previous_operand;
  return operand;
}

char *postfix_evaluator(char **expression, size_t expression_length) {
  
  Operands *operands = malloc(sizeof *operands);
  operands->top = NULL;
  
  for(size_t i = 0; i < expression_length; ++i) {
    if (!strcmp(expression[i], "+") ||
        !strcmp(expression[i], "-") ||
        !strcmp(expression[i], "*") ||
        !strcmp(expression[i], "/")) {
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
