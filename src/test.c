#include "test.h"
#include <curses.h>
#include <math.h>
#include <stdio.h>

int main(int argc, char **argv) {
  char *world = "world!\n";
  double x = sin(90);
  fprintf(stdout, "hello, %s%lf\n", world, x);

  return 0;
}
