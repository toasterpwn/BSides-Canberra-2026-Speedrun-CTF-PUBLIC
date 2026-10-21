#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint64_t canary;

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  canary = rand();
}

void get_fact() {
	uint64_t local_canary = canary;

	char funfact[0x40];

	printf("Tell me a fun fact\n");
	fread(stdin, 0x80, 1, funfact);

	if (local_canary != canary) {
		_exit(1);
	}
}

__attribute__((force_align_arg_pointer))
void spooky() {
	system("/bin/sh");
}

int main(void) {
	setup();
	get_fact();
} 

