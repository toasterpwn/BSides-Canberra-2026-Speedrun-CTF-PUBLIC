# mindtwist

| Author           | **Round** | **Player 1** | **Player 2** | **Winner** |
| ---------------- | --------- | ------------ | ------------ | ---------- |
| ItsIronicIInsist | Finals    |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

Mindtwist is a very basic implementation of a reduced version of brainfuck, where we don't even implement '[' or ']'.
The cell array is stored globally, and there is no bounds checking for the '<' and '>' operations, meaning we can move the cell-index out of bounds.

Before the cell array is the GOT entry for `putchar`. If we move the cell-index to point to it, we can then use the `,` command to read in input and overwrite the entry.

Then, we can trigger the execution of our hijacked GOT entry with a '.' in the brainfuck.

A win function has been provided (and without PIE, it's address is known at compile-time). Once we jump to it, we have a shell.

</details>
