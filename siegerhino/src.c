#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>

#define ARENA_SIZE 0x10000
#define ALLOCS_CAPACITY 0x10

void setup() {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

enum operation {
	ALLOC = 1,
	FREE,
	GET
};

struct chunk {
	struct chunk * next;
	size_t size;
};

struct allocator {
	struct chunk * head;
};

struct allocator allocator_init() {
	struct allocator a;
	a.head = mmap(NULL, ARENA_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (a.head == MAP_FAILED) {
		perror("Map failed");
		exit(1);
	}

	a.head->next = NULL;
	a.head->size = ARENA_SIZE;

	return a;
}

void remove_chunk(struct allocator * a, struct chunk * chunk) {
	struct chunk * prev = a->head;

	if (a->head == chunk) {
		a->head = chunk->next;
		return;
	}

	while(prev->next != chunk) {
		prev = prev->next;
	}

	prev->next = chunk->next;
	return;
}

void split_chunk(struct allocator * a, struct chunk * chunk, size_t split_sz) {
	struct chunk * new_chunk = (struct chunk*)(((uintptr_t)chunk) + split_sz);
	struct chunk * prev = a->head;

	new_chunk->next = chunk->next;
	new_chunk->size = chunk->size - split_sz;

	if (a->head == chunk) {
		a->head = new_chunk;
		return;
	}

	while(prev->next != chunk) {
		prev = prev->next;
	}

	prev->next = new_chunk;
	return;
}

void * allocator_alloc(struct allocator * a, size_t size) {
	struct chunk * cur = a->head;
	while (cur) {
		if (cur->size < size) {
			continue;
		} else if (cur->size == size) {
			remove_chunk(a, cur);
			return cur;
		} else {
			split_chunk(a, cur, size);
			return cur;
		}
	}

	return NULL;
}

void allocator_free(struct allocator * a, void * alloc) {
	struct chunk * c = alloc;
	c->next = a->head;
	a->head = c;
}

void menu() {
	printf("1.  Alloc\n");
	printf("2.  Free\n");
	printf("3.  Get\n");
	printf("> ");
}

void handle_alloc(struct allocator * a, void ** alloc_arr) {
	size_t alloc_size = 0;
	void * alloc = NULL;

	printf("Select allocation size.\n");
	printf("> ");

	scanf("%ld%*c", &alloc_size);

	alloc = allocator_alloc(a, alloc_size);

	printf("Enter alloc contents.\n");
	printf("> ");

	fread(alloc, 1, alloc_size, stdin);

	for (int i = 0 ; i < ALLOCS_CAPACITY ; i++) {
		if (alloc_arr[i] == NULL) {
			alloc_arr[i] = alloc;
			break;
		}
	}
}

void handle_free(struct allocator * a, void ** alloc_arr) {
	size_t arr_idx = 0;

	printf("Select chunk to free.\n");
	printf("> ");

	scanf("%ld%*c", &arr_idx);

	allocator_free(a, alloc_arr[arr_idx]);
}

void spooky(void) {
	system("/bin/sh");
}


int main(void) {
	setup();

	struct allocator a = allocator_init();
	void * allocs[ALLOCS_CAPACITY] = { 0 };
	int op = 0;

	while (true) {
		menu();
		scanf("%d%*c", &op);

		switch (op) {
			case ALLOC:
				handle_alloc(&a, allocs);
				break;
			case FREE:
				handle_free(&a, allocs);
				break;
			default:
				exit(0);
		}

	}
}
