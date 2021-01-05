# AOC 2020
These are my solutions to the [Advent of Code 2020](https://adventofcode.com/2020) problems. Each problem consists of two parts, (denoted as A and B), and a single input file.

Days 16 and 21 are written in [Pike](https://pike.lysator.liu.se/). Run a program using:
```
$ pike src/16A.pike < input/16
```

The rest are written in [C](https://en.wikipedia.org/wiki/C_(programming_language)). Run a program using:
```
$ clang src/01A.c [optional: -O3] [-Isrc (for days 4 and 7)] [-lm (for day 25)]
$ ./a.out < input/01
```

**exceptions**:
- Day 15 has only one C file and no input file
- Day 19 has only one C file and two separate input files
- Day 23 has no input file
- Day 25 has no input file
