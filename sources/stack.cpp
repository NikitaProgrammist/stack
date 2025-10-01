#include <stdio.h>
#include <stdlib.h>

#include "private_stack.h"
#include "check_stack.h"

StackErr stackInit(Stack ** stack) {
  *stack = (Stack *) malloc(sizeof(Stack));
  if (!*stack) {
    return CREATE_FAILED;
  }

  const size_t default_size = 10;
  (*stack)->first_canary = (*stack)->last_canary = 0xFEE1DEAD;
  (*stack)->size = 0;
  (*stack)->capacity = default_size;
  (*stack)->data = (stack_t *) calloc((*stack)->capacity, sizeof(stack_t));

  if (!(*stack)->data) {
    return CALLOC_FAILED;
  }

  stackVerify(*stack);
  return SUCCESS;
}

StackErr stackPush(Stack * stack, stack_t elem) {
  stackVerify(stack);
  stack->data[stack->size++] = elem;

  if (stack->size >= stack->capacity) {
    stack->capacity = 2 * stack->capacity;
    stack->data = (stack_t *) realloc(stack->data, stack->capacity * sizeof(stack_t));

    if (!stack->data) {
      return REALLOC_FAILED;
    }

  }
  printf("%lf %zu\n", stack->data[0], stack->size);
  stackVerify(stack);
  return SUCCESS;
}

StackErr stackPop(Stack * stack, stack_t * elem) {
  if (!elem) {
    return NULL_POINTER;
  }
  stackVerify(stack);

  if (stack->size > 0) {
    *elem = stack->data[--stack->size];
    stackVerify(stack);
    return SUCCESS;
  }

  return POP_FAILED;
}

StackErr stackDestroy(Stack * stack) {
  stack->first_canary = stack->last_canary = stack->size = stack->capacity = 0;
  free(stack->data);
  free(stack);
  return SUCCESS;
}

StackErr stackGetSize(const Stack * stack, size_t * result) {
  stackVerify(stack);
  *result = stack->size;
  stackVerify(stack);
  return SUCCESS;
}

StackErr stackGetCapacity(const Stack * stack, size_t * result) {
  stackVerify(stack);
  *result = stack->capacity;
  stackVerify(stack);
  return SUCCESS;
}
