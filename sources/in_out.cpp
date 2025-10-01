#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "my_printf.h"
#include "in_out.h"

StackErr calcCycle() {
  char * line = NULL;
  stack_t result = 0;
  size_t n = 0;
  while (true) {
    getline(&line, &n, stdin);
    if (!line) {
      return ALLOC_FAILED;
    }

    StackErr err = calculator(line, &result);
    if (err != SUCCESS) {
      free(line);
      return err;
    }

    n = 0;
    free(line);
  }
  printf("%lg\n", result);
  return SUCCESS;
}

StackErr calculator(char * expression, stack_t * result) {
  Stack * operands = NULL;
  size_t size = 0;

  StackErr err = stackInit(&operands);
  if (err != SUCCESS) {
    stackDestroy(operands);
    return err;
  }

  stack_t operand = 0;
  char * startptr = expression;
  char * endptr = NULL;
  while (true) {
    operand = strtod(startptr, &endptr);
    if (startptr == endptr) {
      break;
    }
    startptr = endptr;

    err = stackPush(operands, operand);
    if (err != SUCCESS) {
      stackDestroy(operands);
      return err;
    }
  }

  size_t index = 0;
  stack_t operand_1 =  0, operand_2 = 0;
  while (endptr[index] != '\0') {
    if (endptr[index] == ' ') {
      index++;
      continue;
    }

    err = stackPop(operands, &operand_1);
    if (err != SUCCESS) {
      stackDestroy(operands);
      return err;
    }

    err = stackPop(operands, &operand_2);
    if (err != SUCCESS) {
      stackDestroy(operands);
      return err;
    }

    if (endptr[index] == '+') {
      err = stackPush(operands, operand_1 + operand_2);
      printf("%lf %lf\n", operand_1, operand_2);
      if (err != SUCCESS) {
        stackDestroy(operands);
        return err;
      }
    }
    else if (endptr[index] == '-') {
      err = stackPush(operands, operand_1 - operand_2);
      if (err != SUCCESS) {
        stackDestroy(operands);
        return err;
      }
    }

    else if (endptr[index] == '*') {
      if (endptr[index + 1] != '*') {
        err = stackPush(operands, operand_1 * operand_2);
        if (err != SUCCESS) {
          stackDestroy(operands);
          return err;
        }
      }
      else {
        err = stackPush(operands, pow(operand_1, operand_2));
        if (err != SUCCESS) {
          stackDestroy(operands);
          return err;
        }
      }
    }

    else if (endptr[index] == '/') {
      err = stackPush(operands, operand_1 / operand_2);
      if (err != SUCCESS) {
        stackDestroy(operands);
        return err;
      }
    }

    else {
      stackDestroy(operands);
      return INCORRECT_EXPRESSION;
    }

    index++;
  }
  err = stackGetSize(operands, &size);
  if (err != SUCCESS) {
    stackDestroy(operands);
    return err;
  }
  if (size != 1) {
    stackDestroy(operands);
    return INCORRECT_EXPRESSION;
  }

  err = stackPop(operands, result);
  if (err != SUCCESS) {
    stackDestroy(operands);
    return err;
  }
  return SUCCESS;
}

void errorsParser(StackErr error) {
  switch (error) {
    case SUCCESS:
      break;
    case ASSERTED:
      break;
    case CREATE_FAILED:
      colorPrintf(RED, PRIMARY, "Ошибка при создании стека.");
      break;
    case NULL_POINTER:
      colorPrintf(RED, PRIMARY, "В функцию передан нулевой указатель.");
      break;
    case POP_FAILED:
      colorPrintf(RED, PRIMARY, "Попытка взять элемент из пустого стека.");
      break;
    case ALLOC_FAILED:
      colorPrintf(RED, PRIMARY, "Ошибка при выделении памяти в стандартной функции.");
      break;
    case CALLOC_FAILED:
      colorPrintf(RED, PRIMARY, "Ошибка при выделении памяти.");
      break;
    case REALLOC_FAILED:
      colorPrintf(RED, PRIMARY, "Ошибка при реаллокации.");
      break;
    case INCORRECT_EXPRESSION:
      break;
    case CHECK_FAILED:
      colorPrintf(RED, PRIMARY, "Стек поврежден.");
      break;
    default:
      colorPrintf(RED, PRIMARY, "Непредвиденная ошибка.");
      break;
  }
}
