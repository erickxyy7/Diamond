#ifndef UTILS_H
#define UTILS_H 1

#include <stdbool.h>

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

bool isalpha_azAZ_only(char ch) {
  if (ch < 65 ||
      ch > 90 && ch < 97 ||
      ch > 122)
    return false;
  return true;
}

bool isdigit_09_only(char ch) {
  if (ch < 48 || ch > 57)
    return false;
  return true;
}

#endif /* utils.h */
