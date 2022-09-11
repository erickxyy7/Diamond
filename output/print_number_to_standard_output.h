#ifndef PRINT_NUMBER_TO_STANDARD_OUTPUT
#define PRINT_NUMBER_TO_STANDARD_OUTPUT 1

/**
 * `token` needs to be a number token.
 */
void print_number_to_standard_output(char *token) {
  for(size_t i = 0; token[i]; ++i) {
    if (token[i] == '.') {
      printf("%lf\n", atof(token));
      return;
    }
  }
  printf("%d\n", (int)atof(token));
}

#endif /* print_number_to_standard_output.h */
