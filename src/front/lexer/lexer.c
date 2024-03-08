#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "front/lexer/keywords.h"
#include "front/lexer/number.h"
#include "log.h"

static int
isKeyword(char* buf, size_t* offset, size_t len) {
  log_debug("keywords size is %lu\n", sizeof(c90KeyWords) / sizeof(char*));
  for (size_t i = 0; i < sizeof(c90KeyWords) / sizeof(char*); i++) {
    if (0 == strncmp(c90KeyWords[i], buf + *offset, len)) {
      log_debug("get token {%s}\n", c90KeyWords[i]);
      return 1;
    }
  }
  return 0;
}

int
parseIdent(char* buf, size_t* offset) {
  size_t off = *offset;
  if (isalpha(buf[off]) || '_' == buf[off]) {
  } else {
    log_error("invalid token %s", buf + off);
    return 1;
  }
  for (;;) {
    if (isalnum(buf[off]) || '_' == buf[off]) {
      off += 1;
    } else {
      // *(buf + off) = '\0';
      break;
    }
  }
  log_info("get token [%s]\n", buf + *offset);
  isKeyword(buf, offset, off - *offset);
  *offset = off;
  return 0;
}

static int
skipBlank(char* buf, size_t* offset) {
  for (;;) {
    if (buf[*offset] == '\0') break;
    if (isblank(buf[*offset])) {
      *offset += 1;
    } else {
      break;
    }
  }
  return 0;
}

static int
parseSymbol(char* buf, size_t* offset) {
  switch (buf[*offset]) {
    case '(':
      log_info("get token [(]\n");
      *offset += 1;
      break;
    case ')':
      log_info("get token [)]\n");
      *offset += 1;
      break;
    case '{':
      log_info("get token [{]\n");
      *offset += 1;
      break;
    case '}':
      log_info("get token [}]\n");
      *offset += 1;
      break;
    case ';':
      log_info("get token [;]\n");
      *offset += 1;
      break;
    case '=':
      log_info("get token [=]\n");
      *offset += 1;
      break;
    case '*':
      log_info("get token [*]\n");
      *offset += 1;
      break;
    default:
      log_error("get unknown toke [%s]\n", buf + *offset);
      *offset += 1;
      break;
  }
  return 0;
}

char non_sep[] = {'"', '$', '`', '@', 0x27};
static int
isSep(char sep) {
  if (sep <= 0x7e && sep >= 0x20) {
    if (isalnum(sep) || sep == '_') {
      return 0;
    }
    for (int i = 0; i < 5; i++) {
      if (sep == non_sep[i]) return 0;
    }
    return 1;
  } else {
    return 1;
  }
  return 1;
}

static int
parse(char* buf, size_t* offset) {
  size_t current_offset = *offset;
  size_t new_offset = 0;

  for (;;) {
    new_offset = 0;
    char* token_buf = NULL;
    size_t len = 0;
    for (;;) {
      len += 1;
      if (isSep(buf[*offset + len])) break;
    }
    token_buf = strndup(buf + *offset, len);
    token_buf[len] = '\0';
    log_fatal("read the token [%s]\n", token_buf);
    *offset += len;
    skipBlank(buf, offset);
    if (isdigit(token_buf[new_offset])) {
      // possible number
      parseDigit(token_buf, &new_offset);
    } else if (isalpha(token_buf[new_offset]) || '_' == token_buf[new_offset]) {
      parseIdent(token_buf, &new_offset);
    } else if (isblank(token_buf[new_offset])) {
      new_offset += 1;
    } else if ('\n' == token_buf[new_offset]) {
      break;
    } else {
      parseSymbol(token_buf, &new_offset);
    }
  }

  return 0;
}

int
toToken(FILE* fp) {
  ssize_t readLen;
  char* line = NULL;
  size_t len = 0;
  for (; (readLen = getline(&line, &len, fp)) != -1;) {
    log_debug("[%s]", line);
    size_t start_off = 0;
    parse(line, &start_off);
  }
  if (line) free(line);
  return 0;
}
