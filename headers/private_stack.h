#ifndef PRIVATE_STACK_H
#define PRIVATE_STACK_H

typedef struct Stack Stack;
typedef double stack_t;

struct Stack {
  size_t first_canary;
  stack_t * data;
  size_t size;
  size_t capacity;
  size_t last_canary;
};

enum StackErr {
  SUCCESS,
  ASSERTED,
  CREATE_FAILED,
  NULL_POINTER,
  POP_FAILED,
  ALLOC_FAILED,
  CALLOC_FAILED,
  REALLOC_FAILED,
  INCORRECT_EXPRESSION,
  CHECK_FAILED
};

StackErr stackInit(Stack ** stack);
StackErr stackPush(Stack * stack, stack_t elem);
StackErr stackPop(Stack * stack, stack_t * elem);
StackErr stackDestroy(Stack * stack);
StackErr stackGetSize(const Stack * stack, size_t * result);
StackErr stackGetCapacity(const Stack * stack, size_t * result);

#endif // PRIVATE_STACK_H
