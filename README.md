## json-utils ##
---

A group of utility applications to make working with the JSON file format easier, especially for shell scripting.

---

### Tools ###
  - `jsonread` - reads a field from a specified JSON file.
  - `jsonwrite` - writes a field (and optional sub-fields) and its value to a specified JSON file.
  - `jsonsemver` - implementation of semantic versioning (semver.org) using JSON to store the version data.  Includes functionality to auto-increment version numbers, making automating version numbers with scripts easy.
  - `jsonpp` - pretty-prints a JSON file.

---

### Requirements ###
`json-utils` requires the `json-c` library, which can be found on GitHub: https://github.com/json-c/json-c

---
### Building json-utils ###
  To compile `json-utils`, simply run make:

  `$ make all`

  The compiled files will be located in `./build/`.

---
### Examples ###
---
#### jsonread ####

  `jsonread` can read fields in the given JSON file, even if they are nested in an array or object.
  Given the following JSON file:
```javascript
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
```javascript
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

`jsonwrite` is a utility for writing data to a new or existing JSON file.
The syntax is `jsonwrite file.json field [sub-field, ...] new_value`

  - `$ jsonwrite test.json hello world "hello world!"` writes the following JSON to test.json:
```javascript
{
  "hello":{
    "world":"hello world!"
  }
}
```
You may specify an unlimited number of sub fields, such as:
  - `$ jsonwrite test.json one two three four five 5`

You may also just specify one field:
  - `$ jsonwrite test.json hello "world"` which writes the following to test.json:
```javascript
{
  "hello":"world"
}
```

---
#### jsonsemver ####

`jsonsemver` is a utility for working with semantic version data.  It includes auto-incrementing any of the version numbers, incrementing `patch` by default until it reaches 100, at which point `minor` is incremented, and `patch` is reset to 0.  It is especially useful if you need to manage a project/application version using scripts.

Given the following JSON file, `app-version.json`:

```javascript
{
  "major":7,
  "minor":1,
  "patch":5,
  "prerelease":"beta"
}
```

`$ jsonsemver app-version.json`
`$ jsonsemver app-version.json -s` outputs "7.1.6-beta", since the first time it was executed, it incremented the `patch` field.
Calling `jsonsemver` with the `-s` parameter outputs the version string ONLY, and does not auto-increment the version number.


---
#### jsonpp ####

`jsonpp` is a simple utility that pretty-prints the contents of a JSON file.

Given the following `test.json` file:
```javascript
{"hello":{"world":"hello world!"}}
```
  - `$ jsonpp test.json` outputs the following:
```javascript
{
  "hello":{
    "world":"hello world!"
  }
}
```

---
### Known Bugs ###
  - jsonwrite: crash when overwriting an existing field with sub-fields

---
### TODO ###
  - add full support to jsonsemver for command line flag processing
  - ?

---
### License ###
---
The `json-utils` project is open source and is available under the <a href="LICENSE">MIT license</a>.