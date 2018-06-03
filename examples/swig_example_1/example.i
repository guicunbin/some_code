%module example

%{

#define SWIG_FILE_WITH_INIT
#include "./example.hpp"

%}

int fact(int n);
