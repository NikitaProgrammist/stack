#ifdef CHECK

#ifndef CHECK_STACK_H
#define CHECK_STACK_H

#define stackVerify(stack) {                                                   \
    if (verify(stack)) {                                                       \
        printErrorLines("../" __FILE__, __PRETTY_FUNCTION__, __LINE__);        \
        return CHECK_FAILED;                                                   \
    }                                                                          \
}

#define checkStatement(arg) {                                                  \
    if (arg) {                                                                 \
        colorPrintf(RED, BOLD, "\nStack died, because: " #arg "\n");           \
        dump(stack);                                                           \
        return INVALID;                                                        \
    }                                                                          \
}

#define myAssert(arg) {                                                        \
    if (!(arg)) {                                                              \
        colorPrintf(RED, BOLD, "\nAssertion failed: " #arg "\n");              \
        printErrorLines("../" __FILE__, __PRETTY_FUNCTION__, __LINE__);        \
        return ASSERTED;                                                       \
    }                                                                          \
}

enum Errors {
  VALID,
  INVALID
};

Errors verify(const Stack * stack);
void dump(const Stack * stack);
void printErrorLines(const char * file, const char * func, size_t line_number);

#endif // CHECK_STACK_H

#else

#define stackVerify(stack)
#define myAssert(arg)

#endif // CHECK
