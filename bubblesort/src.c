#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static char flag[128];

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  FILE* f = fopen("flag.txt", "r");
  fgets(flag, sizeof(flag), f);
  fclose(f);
}

void win() {
    puts(flag);
}

void bubblesort(uint64_t* nums, size_t count) {
    for (size_t i = 0; i < count - 1; i++)
    {
        bool swapped = false;
        for (size_t j = 0; j < count - i - 1; j++)
        {
            if(j > 100) break;

            if(nums[j] > nums[j + 1]) {
                nums[j] ^= nums[j+1];
                nums[j+1] ^= nums[j];
                nums[j] ^= nums[j+1];
                
                swapped = true;
            }
        }

        if(!swapped) break;
    }
}

int main() {
    size_t count;
    uint64_t nums[100] = {0};

    setup();

    for (count = 0; count < sizeof(nums); count++)
    {
        printf("number? ");
        scanf("%lu", &nums[count]);
        printf("\ngot: %lu\n", nums[count]);

        if(nums[count] == 66+1) { // this number is banned
            break;
        }
    }

    if(count < 2) return 1;

    printf("Before Sorting: [%lu", nums[0]);
    for (size_t i = 0; i < count; i++)
    {
        printf(", %lu", nums[i + 1]);
    }
    printf("]\n");

    bubblesort(nums, count);    

    printf("After Sorting: [%lu", nums[0]);
    for (size_t i = 0; i < count; i++)
    {
        printf(", %lu", nums[i + 1]);
    }
    printf("]\n");
}
