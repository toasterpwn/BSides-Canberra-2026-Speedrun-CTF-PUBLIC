# format

| Author     | **Round** | **Player 1** | **Player 2** | **Winner** |
| ---------- | --------- | ------------ | ------------ | ---------- |
| toasterpwn | Quals     |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

The challenge passes untrusted user input into `printf` which leads to a "format string bug"

```c
read(0, buf, sizeof(buf));
printf(buf);
```

When `printf` accesses an argument that is greater than `6` (there are 6 register arguments in the x86_64 calling convention) it will read extra arguments off of the stack.

Since our input is on the stack, we can provide an index that user our own input as an argument to a format specifier. The `%s` format specifier takes a pointer to a string, so by providing the address of the flag, we can "arbitrary read" it from global memory.

</details>
