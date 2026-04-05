#include <stdarg.h>
#include <stdio.h>

enum drink {
  MUDSLIDE,
  FUZZY_NAVEL,
  MONKEY_GLAND,
  ZOMBIE,
};

double price(enum drink d) {
  switch (d) {
  case MUDSLIDE:
    return 6.79;
  case FUZZY_NAVEL:
    return 5.31;
  case MONKEY_GLAND:
    return 4.82;
  case ZOMBIE:
    return 5.89;
  }
  return 0;
}

double total(int args, ...) {
  double total = 0;
  va_list drinks;
  va_start(drinks, args);
  int i;
  for (i = 0; i < args; i++) {
    enum drink d = va_arg(drinks, enum drink);
    total += price(d);
  }
  va_end(drinks);
  return total;
}

int main() {
  printf("Price is %.2f\n", total(2, MONKEY_GLAND, MUDSLIDE));
  printf("Price is %.2f\n", total(3, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));
  printf("Price is %.2f\n", total(1, ZOMBIE));
  return 0;
}
