#include <stdio.h>

#include "stack.h"
#include "in_out.h"

int main() {
  Stack * stack = NULL;
  StackErr error = stackInit(&stack);
  size_t * ptr = (size_t *) stack;
  *ptr = 0;
  stackPush(stack, 10);
  stackDestroy(stack);
  error = calcCycle();
  errorsParser(error);
  return 0;
}
