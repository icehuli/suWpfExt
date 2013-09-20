/* File : myExtMain.i */
%module MyExtMain


%{
#include "myExtMain.h"
%}

/* Let's just grab the original header file here */
%include "myExtMain.h"