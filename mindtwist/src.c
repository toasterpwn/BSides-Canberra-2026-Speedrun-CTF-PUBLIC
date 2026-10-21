#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROG 0x100
#define NUM_CELLS 0x100
uint8_t cells[NUM_CELLS] = { 0 };
uint64_t cidx = 0;

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}

void handle_cmd(char cmd) {
	switch (cmd) {
		case '>':
			cidx++;
			break;
		case '<':
			cidx--;
			break;
		case '+':
			cells[cidx]++;
			break;
		case '-':
			cells[cidx]--;
			break;
		case '.':
			putchar(cells[cidx]);
			break;
		case ',':
			cells[cidx] = getchar();
			break;
		default:
			exit(1);
	}

}

void spooky() {
	system("/bin/sh");
}

int main(void) {
	setup();

	char prog[MAX_PROG] = { 0 };
	fgets(prog, MAX_PROG, stdin);
	
	for (int i = 0 ; i < MAX_PROG ; i++) {
		handle_cmd(prog[i]);
	}
} 

