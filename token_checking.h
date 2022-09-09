#ifndef TOKEN_CHECKING_H
#define TOKEN_CHECKING_H 1

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * Returns true if `token` is of type number, else, returns false.
 */
bool is_number(char *token) {
  size_t total_points = 0;
  for(size_t i = 0, l = strlen(token); i < l; ++i)
    if (token[i] == '.')
      ++total_points;
  if (total_points > 1)
    return false;
  
  for(size_t i = 0, l = strlen(token); i < l; ++i) {
    if (!isdigit(token[i]) && token[i] != '.')
      return false;
  }
  
  return true;
}

/**
 * Returns true if `token` is of type string, else, returns false.
 * 
 * Todo: throw error if the string is invalid. E.g: has an invalid escape character.
 */
bool is_string(char *token) {
  size_t token_length = strlen(token);
  if (token[0] == '\'' && token[token_length - 1] == '\'')
    return true;
  if (token[0] == '"' && token[token_length - 1] == '"')
    return true;
  return false;
}

#endif /* token_checking.h */
