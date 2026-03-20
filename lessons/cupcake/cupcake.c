#include <stdio.h>

typedef union {
  float weight;
  int count;
} cupcake;

int main() {
  cupcake order = {2};
  // this is bad code no worries i know
  printf("Cupcakes quantity: %i\n", order.count);
  return 0;
}
