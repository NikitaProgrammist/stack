#ifndef IN_OUT_H
#define IN_OUT_H

StackErr calcCycle();
StackErr calculator(char * expression, stack_t * result);
void errorsParser(StackErr error);

#endif // IN_OUT_H
