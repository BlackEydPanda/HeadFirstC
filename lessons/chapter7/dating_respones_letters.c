#include <stdio.h>

enum response_type { DUMP, SECOND_CHANCE, MARRIAGE };
typedef struct {
  char *name;
  enum response_type type;
} response;

void dump(response r) {
  printf("Dear %s, \n", r.name);
  puts("Unfortunately your last date contacted us to");
  puts("say that they will not be seeing you again.");
}

void second_chance(response r) {
  printf("Dear %s, \n", r.name);
  puts("Good nes: your last date has asked us to");
  puts("arrange another meeting. Please call ASAP");
}

void marriage(response r) {
  printf("Dear %s, \n", r.name);
  puts("Congratulations! Your last date has contacted");
  puts("us with a proposal of marriage!");
}

int main() {
  response responses[] = {
      {"Mike", DUMP},
      {"Luis", SECOND_CHANCE},
      {"Matt", SECOND_CHANCE},
      {"William", MARRIAGE},
  };

  void (*reply_functions[])(response) = {dump, second_chance, marriage};

  int i;
  for (i = 0; i < 4; i++) {
    reply_functions[responses[i].type](responses[i]);
  }

  return 0;
}
