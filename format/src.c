#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char flag[0x100];

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  int fd = open("flag.txt", O_RDONLY);
  read(fd, flag, sizeof(flag));
  close(fd);
}

int main(void) {
  char buf[0x10] = {};
  setup();
  printf("> ");
  read(0, buf, sizeof(buf));
  printf(buf);
  printf(":)\n");
  return 0;
}
