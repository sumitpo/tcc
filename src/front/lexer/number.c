#include <stddef.h>
#include <stdio.h>

#include "log.h"

static int
parseHex(char* buf, size_t* offset) {
  *offset += 2;
  for (;;) {
    if ((buf[*offset] <= '9' && buf[*offset] >= '0') ||
        (buf[*offset] <= 'f' && buf[*offset] >= 'a') ||
        (buf[*offset] <= 'F' && buf[*offset] >= 'A')) {
      *offset += 1;
    } else {
      break;
    }
  }
  return 0;
}
static int
parseOctal(char* buf, size_t* offset) {
  *offset += 1;
  for (;;) {
    if (!(buf[*offset] <= '7' && buf[*offset] >= '0')) {
      break;
    } else {
      *offset += 1;
    }
  }
  return 0;
}
static int
parseDecimal(char* buf, size_t* offset) {
  do {
    if (!(buf[*offset] <= '9' && buf[*offset] >= '1')) {
      break;
    } else {
      *offset += 1;
    }
    for (;;) {
      if (!(buf[*offset] <= '9' && buf[*offset] >= '0')) {
        break;
      } else {
        *offset += 1;
      }
    }
    return 0;
  } while (0);
  return 1;
}
static int
parseInteger(char* buf, size_t* offset) {
  char first_chr = buf[*offset], snd_chr = buf[*offset];
  if ('0' == first_chr && ('x' == snd_chr || 'X' == snd_chr)) {
    parseHex(buf, offset);
  } else if ('0' == first_chr) {
    parseOctal(buf, offset);
  } else {
    parseDecimal(buf, offset);
  }
  return 0;
}
static int
parseFloat(char* buf, size_t* offset) {
  log_warn("not implemented\n");
  printf("%c\n", buf[*offset]);
  return 0;
}
int
parseDigit(char* buf, size_t* offset) {
  parseInteger(buf, offset);
  if (0) {
    parseFloat(buf, offset);
  }
  return 0;
}
