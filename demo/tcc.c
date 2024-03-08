#include <stdio.h>

#include "front/lexer/lexer.h"
#include "log.h"

int
main(int argc, char* argv[]) {
#ifdef LOG_LEVEL_TRACE
  log_set_level(0);
#elif LOG_LEVEL_DEBUG
  log_set_level(1);
#elif LOG_LEVEL_INFO
  log_set_level(2);
#elif LOG_LEVEL_WARN
  log_set_level(3);
#elif LOG_LEVEL_ERROR
  log_set_level(4);
#elif LOG_LEVEL_FATAL
  log_set_level(5);
#else
#endif
  if (argc <= 1) return 0;
  FILE* fp = fopen(argv[1], "r");
  toToken(fp);
  fclose(fp);
  return 0;
}
