#ifndef BOOLEAN_H
#define BOOLEAN_H 1

#include <stdbool.h>

/* Tests if a token is true or not.
 * 
 * A number token is false when it is 0.
 */
bool is_true(char *token) {
  if (is_number(token)) {
    double token_as_double = atof(token);
    if (token_as_double == 0)
      return false;
    return true;
  }
}

#endif /* boolean.h */
