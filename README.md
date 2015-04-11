## json-utils ##
---

A group of utility applications to make working with the JSON file format easier, especially when (bash) scripting.

---

### Tools ###
  - `jsonread` - reads a field from a specified JSON file.
  - `jsonwrite` - writes a field and its value to a specified JSON file.
  - `jsonpp` - pretty-prints a JSON file.

---

### Examples ###
---
#### jsonread ####
---
  `jsonread` can read fields in the given JSON file, even if they are nested in an array or object.
  Given the following JSON file:
```
{
  "obj": {
    "sub1": {
      "one": 1,
      "two": 2
    }
}
```
  `jsonread` can read any of these fields:

  - `$ jsonread myfile.json obj sub1` returns `{ "one": 1, "two": 2 }`
  - `$ jsonread myfile.json obj sub1 one` returns `1`
  - `$ jsonread myfile.json obj sub1 two` returns `2`

  `jsonread` can also access array items:

  Given the following JSON file:
```
{
  "my_array":[
    [2,3,4],
    {
      "five":5,
      "six":6
    },
    7
  ],
}
```
  - `$ jsonread myfile.json my_array` returns `[ [ 2, 3, 4 ], { "five": 5, "six": 6 }, 7 ]`
  - `$ jsonread myfile.json my_array 0` returns `[ 2, 3, 4 ]`
  - `$ jsonread myfile.json my_array 0 1` returns `3`
  - `$ jsonread myfile.json my_array 1 five` returns `5`

---
#### jsonwrite ####
---
  - @todo

---
### License ###