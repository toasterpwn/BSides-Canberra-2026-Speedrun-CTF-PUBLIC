#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY 0x100

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}

struct hashmap {
	uint64_t buckets[63];
	uint64_t (*get)(struct hashmap *, char*);
	void (*set)(struct hashmap *, char*, uint64_t);
	void (*delete)(struct hashmap *, char *);
};

enum operations {
	GET = 1,
	SET,
	DELETE,
};

size_t hash(char *str) {
    size_t hash = 5381;
    size_t c;

    while (c = *str++) 
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % 0x63;
}

uint64_t hashmap_get(struct hashmap * map, char * key) {
	size_t bidx = hash(key);
	return map->buckets[bidx];
}

void hashmap_set(struct hashmap * map, char * key, uint64_t value) {
	size_t bidx = hash(key);
	map->buckets[bidx] = value;
}

void hashmap_delete(struct hashmap * map, char * key) {
	size_t bidx = hash(key);
	map->buckets[bidx] = 0;
}

struct hashmap hashmap_new() {
	struct hashmap h = { 0 };
	h.get = hashmap_get;
	h.set = hashmap_set;
	h.delete = hashmap_delete;
	return h;
}

void menu() {
	printf("1. Get\n");
	printf("2. Set\n");
	printf("3. Delete\n");
	printf("Please enter an option: ");
}

void handle_get(struct hashmap * map) {
	char key[MAX_KEY] = { 0 };

	printf("Please enter the key: ");
	fgets(key, MAX_KEY, stdin);
	key[strcspn(key, "\n")] = '\0';

	printf("%lx\n", map->get(map, key));
}

void handle_set(struct hashmap * map) {
	char key[MAX_KEY] = { 0 };
	uint64_t value = 0;

	printf("Please enter the key: ");
	fgets(key, MAX_KEY, stdin);
	key[strcspn(key, "\n")] = '\0';
	printf("Please enter the value: ");
	scanf("%ld%*c", &value);

	map->set(map, key, value);
}

void handle_delete(struct hashmap * map) {
	char key[MAX_KEY] = { 0 };

	printf("Please enter the key: ");
	fgets(key, MAX_KEY, stdin);
	key[strcspn(key, "\n")] = '\0';

	map->delete(map, key);
}

int main(void) {
	setup();
	printf("A gift: %p\n", system);


	struct hashmap h = hashmap_new();

	while(true) {
		int op = 0;

		menu();
		scanf("%d%*c", &op);
		switch (op) {
			case GET:
				handle_get(&h);
				break;
			case SET:
				handle_set(&h);
				break;
			case DELETE:
				handle_delete(&h);
				break;
			default:
				exit(0);
		}
	}
} 
