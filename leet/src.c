#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

int main() {
  setup();

  struct {
    char buf[0x10];
    int x;
  } chal;

  chal.x = 0x42;

  printf(":> ");
  read(0, chal.buf, sizeof(chal));

  if (chal.x == 0x13371337) {
    system("cat flag.txt");
    return 1;
  }

  printf("Oh no!\n");

  return 0;
}
