# get_next_line

A project that implements a function capable of reading from a file descriptor and returning one line at a time, without losing data between calls, regardless of the buffer size used.


## Summary

The get_next_line project aims to recreate a line-reading utility similar to the standard getline function, reinforcing a deep understanding of:

- Static variables and persistent memory between function calls.
- File descriptors and the `read()` system call.
- Dynamic memory management and string manipulation in C.

Requirements:

- get_next_line.c, get_next_line_utils.c, and get_next_line.h

(and the bonus counterparts)

Constraints:

- 5 functions per file
- 25 lines per function
- Single static variable (bonus part)
- Norm compliance

## Methodology and Optimization

Typical `get_next_line()` implementations dynamically allocate and reallocate heap memory frequently.
This project takes a different approach by reducing heap allocations. Instead of continuously reallocating and copying buffers, this version:

- Maintains a temporal buffer that grows in powers of two as needed (with a cap)
- Minimizes heap operations by only reallocating when the buffer capacity is exceeded
- Achieves significantly fewer heap allocations, improving performance (less malloc/free overhead)

Here's an extreme example with the two implementations: 140,000+ allocations → 64 allocations with the power-of-two growth strategy.

![Allocation Comparison](https://i.imgur.com/A70rJ8V.png)

## Usage

Compile your project with:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42
```
(or any size you'd like)

## Notes

Works with any `BUFFER_SIZE` > 0.

Handles multiple file descriptors simultaneously.

## Contact

If you have any questions, suggestions, or comments, feel free to contact me:
- Email: guillekm92@gmail.com