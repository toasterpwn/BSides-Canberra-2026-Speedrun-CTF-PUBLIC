#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct stat st = {};
  int ret = 0;
  size_t cnt = 0;
  FILE *fp = NULL;
  char *filebuf = NULL;

  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return -1;
  }

  if (strstr(argv[1], "flag.txt")) {
    printf("Permission Denied\n");
    return -1;
  }

  ret = lstat(argv[1], &st);
  if (ret) {
    perror("lstat");
    return -1;
  }

  if (S_ISLNK(st.st_mode)) {
    printf("Permission Denied\n");
    return -1;
  }

  filebuf = malloc(st.st_size);
  if (!filebuf) {
    perror("malloc");
    return -1;
  }

  fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen");
    return -1;
  }

  cnt = fread(filebuf, 1, st.st_size, fp);
  if (!cnt) {
    printf("Empty File\n");
    return -1;
  }

  fwrite(filebuf, 1, cnt, stdout);
  return 0;
}
