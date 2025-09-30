#include <stdio.h>

#include "stack.h"
#include "my_printf.h"
#include "in_out.h"

StackErr calculator(const char * expression) {

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
    case CALLOC_FAILED:
      colorPrintf(RED, PRIMARY, "Ошибка при выделении памяти.");
      break;
    case REALLOC_FAILED:
      colorPrintf(RED, PRIMARY, "Ошибка при реаллокации.");
      break;
    case CHECK_FAILED:
      colorPrintf(RED, PRIMARY, "Стек поврежден.");
      break;
    default:
      colorPrintf(RED, PRIMARY, "Непредвиденная ошибка.");
      break;
  }
}
