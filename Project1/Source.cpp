#include <iostream>

typedef int (*InProc)(double);
typedef int* (*OutProc)(char const*);
typedef OutProc(*ComplexFunction)(int, InProc);



