# cmp

| Author     | **Round** | **Player 1** | **Player 2** | **Winner** |
| ---------- | --------- | ------------ | ------------ | ---------- |
| toasterpwn | Quals     |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

The challenge prints the return value of `strncmp` which is the difference of the first 2 non-matching bytes.

```c
int ret = strncmp(buf, admin_password, sizeof(admin_password));
  if (!ret) {
    system("cat flag.txt");
    return 1;
  }

  printf("[ERROR] Admin login returned %d\n", ret);
```

By sending null bytes, we are returned -first_incorrect_password_character. We can use this to build up the password byte by byte.

</details>
