#ifndef PRINT_STRING_TO_STANDARD_OUTPUT
#define PRINT_STRING_TO_STANDARD_OUTPUT 1

#include <stdio.h>

void print_string_to_standard_output(char *str) {
  ++str;
  while (*(str + 1)) {
    putchar(*str);
    ++str;
  }
  putchar('\n');
}

#endif
