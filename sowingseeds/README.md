# sowingseeds

| Author           | **Round**  | **Player 1** | **Player 2** | **Winner** |
| ---------------- | ---------- | ------------ | ------------ | ---------- |
| ItsIronicIInsist | Tiebreaker |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

sowingseeds is a simple tiebreaker challenge. It has no relevant modern protections, but uses a handwritten stack canary implementation.

That stack canary is generated from a call to `rand()` that hasn't been seeded, making it predictable.
Once we bypass the canary, we can just call the win function.

</details>
