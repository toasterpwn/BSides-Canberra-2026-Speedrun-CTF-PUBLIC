# spectrum

| Author     | **Round** | **Player 1** | **Player 2** | **Winner** |
| ---------- | --------- | ------------ | ------------ | ---------- |
| HexF       | Finals    |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

  `add_user` allows us to create users with privilege level INFINITY by setting other user to the currently logged in user.
  Similar we can get a -INFINITY privilege level by setting other user to a user with a higher privilege level, e.g. admin.

  This can get us two accounts, which we can try add the privilege levels together for, giving INFINITY + (-INFINITY) = NaN.
  Using `NaN` in any comparisions will return false, which allows us to bypass both privilege checks for getting the flag.

</details>
