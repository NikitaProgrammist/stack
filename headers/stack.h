#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;
typedef double stack_t;

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

#endif // STACK_H
