# OcelotPride

| Author           | **Round** | **Player 1** | **Player 2** | **Winner** |
| ---------------- | --------- | ------------ | ------------ | ---------- |
| ItsIronicIInsist | Finals    |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

`OcelotPride` implements a basic hashmap, with the key type being strings, and the value type being u64s.

The capacity of the buckets array is 63, but the hashing function ANDs the result with 0x63 instead, meaning the resulting hash value can access out-of-bounds.

If we use that out-of-bounds access to write our u64 into the addresses of one of the function-pointers of the hashbucket struct, we can get code execution.

All we need to then do is trigger the fptr, which we set to `system`, and provide a string key of "/bin/sh".

</details>
