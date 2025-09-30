#ifdef CHECK

#include <stdio.h>

#include "my_printf.h"
#include "private_stack.h"
#include "check_stack.h"

Errors verify(const Stack * stack) {
  const size_t max_capacity = 100000;
  checkStatement(stack->first_canary != 0xFEE1DEAD || stack->last_canary != 0xFEE1DEAD);
  checkStatement(!stack || !stack->data);
  checkStatement(stack->size >= stack->capacity);
  checkStatement(stack->capacity > max_capacity || stack->capacity <= 0);
  return VALID;
}

void dump(const Stack * stack) {
  const size_t max_print = 5;
  if (stack) {

      colorPrintf(RED, BOLD, "stack [%p]\n", stack);
      colorPrintf(RED, BOLD, "    first_canary = %X\n", stack->first_canary);
      colorPrintf(RED, BOLD, "    size = %zu\n", stack->size);
      colorPrintf(RED, BOLD, "    capacity = %zu\n", stack->capacity);

      if (stack->data) {
        colorPrintf(RED, BOLD, "    data [%p]\n", stack->data);

        for (size_t i = 0; i < max_print; i++) {
          if (i < stack->size) {
            colorPrintf(RED, BOLD, "        *[%zu] = %zu\n", i, stack->data[i]);
          }
          else {
            colorPrintf(RED, BOLD, "        [%zu] = %zu (not in stack)\n", i, stack->data[i]);
          }
        }

      }

      else {
        colorPrintf(RED, BOLD, "    Нулевой указатель на массив в стеке.\n");
      }

      colorPrintf(RED, BOLD, "    last_canary = %X\n", stack->last_canary);
  }

  else {
    colorPrintf(RED, BOLD, "Нулевой указатель на стек.\n");
  }
}

void printErrorLines(const char * file, const char * func, size_t line_number) {
  colorPrintf(RED, BOLD, "file: %s:%zu\nfunc: %s\n", file, line_number, func);

  const int MAX_LINE = 150;
  char line[MAX_LINE] = {};
  FILE * fp = fopen(file, "r");

  for (size_t i = 0; i <= line_number; i++) {
    fgets(line, MAX_LINE, fp);
    if (i >= line_number - 2)
      colorPrintf(RED, BOLD, "%zu: %s", i + 1, line);
  }

  fclose(fp);
}

#endif // CHECK
