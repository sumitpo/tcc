#include "misc/util.h"

int
isDigit(char chr) {
  if ('0' <= chr && chr <= '9') return 1;
  return 0;
}

int
isLowerCase(char chr) {
  if ('a' <= chr && chr <= 'z') return 1;
  return 0;
}
int
isUpperCase(char chr) {
  if ('A' <= chr && chr <= 'Z') return 1;
  return 0;
}
