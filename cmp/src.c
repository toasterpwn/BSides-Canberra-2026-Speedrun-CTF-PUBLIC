#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <unistd.h>

char admin_password[0x10];

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

void get_random(char *buf, size_t len) {
  unsigned char c = 0;
  for (int i = 0; i < len; i++) {
    getrandom(&c, 1, 0);
    buf[i] = 'a' + (c % 26);
  }
}

int login() {
  char buf[0x10];
  printf("Login: ");
  if (read(0, buf, sizeof(buf)) != sizeof(buf)) {
    return 0;
  }

  int ret = strncmp(buf, admin_password, sizeof(admin_password));
  if (!ret) {
    system("cat flag.txt");
    return 1;
  }

  printf("[ERROR] Admin login returned %d\n", ret);
  return 0;
}

int main(void) {
  setup();
  get_random(admin_password, sizeof(admin_password));

  while (1) {
    if (login()) {
      break;
    }
  }
  return 0;
}
