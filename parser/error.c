#include "error.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>

void scan_error() {
  fprintf(stderr,"scan error: %s is not a valid character\n", yytext);
  exit(1);
}
