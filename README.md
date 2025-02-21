<!-- vim: set foldlevel=3 nowrap: -->

# cpp-assertion

A simple and modern C++ assertion library.

## Table of Contents

<details>

<summary>Table of Contents</summary>

1. [Features](#features)
2. [Usage](#usage)
3. [Showcase](#showcase)
4. [Run tests](#run-tests)

</details>

## Features

- **Debug breaks**: Supports Clang, GCC (i386 and x86_64), and MSVC.
- **C++20 format messages**: See [`std::format`](https://en.cppreference.com/w/cpp/utility/format/format).
- **Predicate assertions**: Soft assertions can be used within expressions.
- **Release/Debug**: Removes debug information in release builds.
- **ANSI color support**

## Usage

Just copy the header file (`./src/Assert.hpp`) and include it as needed. Take a look at
`/compile_flags.txt` to get a simple example.

### Debug break

Use `DEBUG_BREAK()` to pause program execution when a debugger is attached.

`ASSERT_FATAL()` will also enter in debug mode before terminate the program, su you can inspect the
status before crash.

This macro is disabled when `NDEBUG` is defined. Visit the [assert man page](https://man7.org/linux/man-pages/man0/assert.h.0p.html) for more details on `NDEBUG`.

> [!NOTE]
> *Tested on Linux x86_64 with `Clang`, `GCC`, `codelldb`, and `cppdbg`. All combinations work.*

> [!WARNING]
> *On Debug builds, the program will crash when no debugger is attached. A proper handler to detect
> and ignore this case is planned. Windows provides an API for this, but Linux requires additional
> effort.*

```cpp
int main(int argc, char* argv[]) {
    DEBUG_BREAK(); // <== Code will break right after this point
    std::cout << "Hey, I break the execution";
    return 0;
}
```

### Assertion messages

You can add messages to assertions to improve logging and debuggability.

Modern `std::format` is used internally, so assertions inherit its formatting. See [`std::format`](https://en.cppreference.com/w/cpp/utility/format/format).

```cpp
int main(int argc, char* argv[]) {
    ASSERT_FATAL(false == true); // No message
    ASSERT_FATAL(false == true, "Always crash..");
    ASSERT_FATAL(false == true, "Always crash: {} {}.", "Something", 10);
    ASSERT(true == true, "This won't fail");
    return 0;
}
```

### Predicate assertions

Soft assertions return the result of the evaluated expression.

This feature is intended to support defensive programming by balancing error reporting with clean code.
In `NoDebug` builds, these assertions do not report errors messages but still evaluate the expression.

```cpp
int main(int argc, char* argv[]) {
    if (ASSERT(true == true, "This won't fail")) {
        // Do something ...
    }
    if (!ASSERT(false, "This assertion will fail")) {
        // Adopt early returns. Thanks :)
    }
    return 0;
}
```

## Showcase
![image](https://github.com/user-attachments/assets/9faa89fd-12df-4a9e-adb8-ad8e2b3318f8)


## Run tests

Since fatal assertions terminate the program under test, this library relies on a custom test runner.

The runner generates executables for debug and non-debug modes. Then it run all the tests cases for
both modes.

> [!NOTE]
> *A snapshot testing feature to check test output is planned for the future.*
