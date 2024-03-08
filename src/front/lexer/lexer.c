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
      log_debug("get keyword {%s}\n", c90KeyWords[i]);
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
  // log_info("get token [%s]", buf + *offset);
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
    } else
      break;
  }
  return 0;
}

static int
parseSymbol(char* buf, size_t* offset) {
  switch (buf[*offset]) {
    case '(':
      log_debug("get token [(]");
      *offset += 1;
      break;
    case ')':
      log_debug("get token [)]");
      *offset += 1;
      break;
    case '{':
      log_debug("get token [{]");
      *offset += 1;
      break;
    case '}':
      log_debug("get token [}]");
      *offset += 1;
      break;
    case ';':
      log_debug("get token [;]");
      *offset += 1;
      break;
    case '=':
      log_debug("get token [=]");
      *offset += 1;
      break;
    case '*':
      log_debug("get token [*]");
      *offset += 1;
      break;
    default:
      log_debug("get unknown toke [%s]", buf + *offset);
      *offset += 1;
      break;
  }
  return 0;
}

char non_sep[] = {'"', '$', '`', '@', 0x27};
static int
isSep(char sep) {
  if (sep <= 0x7e && sep >= 0x20) {
    if (isalnum(sep) || sep == '_') return 0;
    for (int i = 0; i < 5; i++)
      if (sep == non_sep[i]) return 0;
    return 1;
  } else
    return 1;
  return 1;
}

static int
parse(char* buf, size_t* offset) {
  size_t new_offset;
  for (;;) {
    skipBlank(buf, offset);
    new_offset = *offset;
    if (isdigit(buf[new_offset])) {
      parseDigit(buf, &new_offset);
    } else if (isalpha(buf[new_offset]) || '_' == buf[new_offset]) {
      parseIdent(buf, &new_offset);
    } else if ('\n' == buf[new_offset])
      break;
    else
      parseSymbol(buf, &new_offset);

    char* token_buf = NULL;
    size_t len = new_offset - *offset;
    token_buf = strndup(buf + *offset, len);
    token_buf[len] = '\0';
    log_info("get token [%s]", token_buf);

    *offset = new_offset;
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
