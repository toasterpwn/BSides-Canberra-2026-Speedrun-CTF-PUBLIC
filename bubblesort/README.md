# bubblesort

| Author     | **Round** | **Player 1** | **Player 2** | **Winner** |
| ---------- | --------- | ------------ | ------------ | ---------- |
| HexF       | Finals    |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

The challenge uses `scanf` to read up to `sizeof(nums)` unsigned longs into a stack array, sort them, then print them out.

The use of `sizeof(nums)` returns the number of bytes in size, not the number of array entries, allowing arbitrary writing onto the stack.

```c
for (count = 0; count < sizeof(nums); count++)
{
    printf("number? ");
    scanf("%lu", &nums[count]);
    printf("\ngot: %lu\n", nums[count]);

    if(nums[count] == 66+1) { // this number is banned
        break;
    }
}
```

The `count` value can be incremented by sending a `+`, which will cause `scanf` to return, but not update the value in `nums[count]`.
This can be used to hop over the stack canary without writing it, allowing the return adresss to be set to the win function.

</details>
