![](cover-get_next_line-bonus.png)

<p align="center">
<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/Keisn1/get-next-line?color=blueviolet" />
<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/Keisn1/get-next-line?color=blue" />
<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/Keisn1/get-next-line?color=brightgreen" />
<img alt="GitHub Lines of Code" src="https://tokei.rs/b1/github/Keisn1/get-next-line?category=code" />
</p>

# Table of contents <span class="tag" data-tag-name="TOC"><span class="smallcaps">TOC</span></span>

  - [What is get\_next\_line?](#what-is-get_next_line)
  - [What are static variables?](#what-are-static-variables)
  - [What is a file descriptor? (open() system
    call)](#what-is-a-file-descriptor-open-system-call)
      - [file status flags (some)](#file-status-flags-some)
  - [What is the read() system-call?](#what-is-the-read-system-call)
      - [Buffer size and count (from
        man)](#buffer-size-and-count-from-man)

# What is get\_next\_line?

The **get\_next\_line** project is part a project inside the **Core
Curriculum of 42school** which teaches about a variety of concepts in
low-level programming. To succeed in this project, students need to
acquire knowledge on *file descriptors* and *static variables* as well
as developing proficiency in handling *memory* and
*preprocessor-directives* as well as the *read()* and *open()* system
call.

The **task** of the project is to write a function that accepts a *file
descriptor* as input and returns a string containing the contents of the
corresponding text file. Each time the function is called, it should
return exactly one line from the file, progressing to the next line with
each subsequent call. It shall also be possible to read from `stdin`.

``` c
char* get_next_line(int fd);
```

Since the length of the line is unknown in advance, we need to set a
`BUFFER_SIZE` beforehand to determine how much data to read from the
file descriptor each time. The `BUFFER_SIZE` may vary, and we should be
able to configure its size during compilation.

``` shell
-D BUFFER_SIZE=n
```

Furthermore, the project sets some constraints. We are not allowed to
use any `seek` function to reposition our read head to the spot just
after a newline. Therefore, we need to manage any excess data by
manipulating the memory where we store our string. Moreover, we cannot
use global variables, and since we need to retain what was read the last
time the function was called, we must store that information in a
`static` variable.

# What are static variables?

*Static variables* are declared inside functions, and their values
remain consistent between function calls. When you declare a *static
variable* within a function, any changes made to it will persist across
subsequent calls to that function. This enables the creation of stateful
functions. Static variables are declared using the `static` keyword.

``` c
#include <stdio.h>

void counter() {
    static int count = 0;  // Static local variable
    count++;
    printf("Count: %d\n", count);
}

int main() {
    counter();  // Output: Count: 1
    counter();  // Output: Count: 2
    counter();  // Output: Count: 3
    return 0;
}
```

# What is a file descriptor? (open() system call)

A *file descriptor* is a small, nonnegative integer that serves as a
reference to an open file description and is unaffected by changes to
the file's pathname.

It acts as an index to an entry in the process's table of open *file
descriptors* and is the return value from the `open` system call.

While using the file descriptor in further calls like `read()`, the
[file
position](https://www.gnu.org/software/libc/manual/html_node/File-Position.html)
is being tracked.

File descriptors are utilized in various system calls such as `read()`,
`write`, `lseek`, and `fcntl`.

They record important information like the *file offset* and *file
status flags*.

When opening a file, the argument flags must include one of the access
modes: `O_RDONLY`, `O_WRONLY`, or `O_RDWR`.

## file status flags (some)

### `O_RDONLY`:

Open for reading only

### `O_WRONLY`:

Open for writing only

### `O_RDWR`:

Open for reading and writing

### `O_CREAT`:

Create the file if it does not exist

### `O_APPEND`:

All writes will be appended to the end of the file

### `O_SYNC`:

Write operations are synchronized, meaning changes are flushed to the
underlying storage device immediately

### `O_CLOEXEC`:

Close the file descriptor when a new program is executed using one of
the `exec` family of functions

### `O_EXCL`:

Exclusive use flag, when used with `O_CREAT`, will cause the call to
fail if the file already exists

### `O_TRUNC`:

Truncate the file to zero length if it already exists

# What is the read() system-call?

``` c
ssize_t read(int fd, void buf[.count], size_t count);
```

The `read` function reads up to `count` bytes from the *file descriptor*
`fd` and saves them into the buffer `buf`.

On success, the return value holds the number of bytes that have been
read and the *file position* is being advanced by that number.

A return value of `0` indicates the end of the file. A return value of
`-1` indicates an error and `errno` is set for further information on
the error.

On error, the change of the file position is unspecified.

It may appear that fewer bytes are read than were requested. This is not
an error. It might just be, that a the process was interrupted or it
reached the end of the file.

## Buffer size and count (from man)

If `count` is zero, `read()` may detect the errors described below.

In the absence of any errors, or if `read()` does not check for errors,
a `read()` with a count of 0 returns zero and has no other effects.

According to POSIX.1, if `count` is greater than `SSIZE_MAX`, the result
is **implementation-defined**; see NOTES for the upper limit on Linux.

On my system, the `ssize_type` was defined via `__ssize_t`, which in
turn is defined as `__SWORD_TYPE` which is a `long int`

``` c
# define __SWORD_TYPE           long int
#define __SSIZE_T_TYPE          __SWORD_TYPE
__STD_TYPE __SSIZE_T_TYPE __ssize_t; /* Type of a byte count, or error.  */
typedef __ssize_t ssize_t;
```
