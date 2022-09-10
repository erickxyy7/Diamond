#ifndef OPERANDS_H
#define OPERANDS_H 1

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

#endif /* operands.h */
