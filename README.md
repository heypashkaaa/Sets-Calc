
# 🧮 Set Calculator (C + Flex + Bison)

A  command-line calculator for Set Theory operations. This project implements a custom programming language utilizing **Flex** (Lexer) and **Bison** (Parser) to process set operations, variable assignments, and conditional logic.

> **Project Status:** Completed 🚀  
> **Course:** Compilers   
> **Language:** C (Standard C99)

-----

## ✨ Features

  - **Set Definitions**: Create and store sets in variables (e.g., `let A = {1, 2}`).
  - **Mathematical Operations**:
      - `+` : Union (A ∪ B)
      - `^` : Intersection (A ∩ B)
      - `-` : Difference (A \\ B)
      - `x` : Cartesian Product (A × B)
  - **Logic & Flow Control**:
      - Comparison: `==`, `!=`
      - Conditional Execution: `if (A == B) DO ... ELSE ...`
  - **Memory Management**: Automatic memory cleanup for temporary sets and variables.

-----

## 🛠️ Installation & Build

### Prerequisites

You need the following tools installed on your system:

  * **C Compiler** (GCC or Clang)
  * **CMake** (Version 3.23+)
  * **Flex** & **Bison** (WinFlexBison for Windows)

### Building with CMake

1.  Clone the repository:

    ```bash
    git clone https://github.com/heypashkaaa/Sets-Calc.git
    cd Sets-Calc
    ```

2.  Create a build directory and run CMake:

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

3.  Run the executable:

    ```bash
    ./set_calc  # On Linux/Mac
    set_calc.exe # On Windows
    ```

-----

## 📖 Usage Guide

Once the program is running, you can enter commands line by line.

Type `help` or `quit` to get some clarification.

```text
> help
```

### 1\. Defining Sets

Use the `let` keyword to assign a set to a variable.

```text
> let A = {1, 2, 3}
Defined A
> let B = {3, 4, 5}
Defined B
```

### 2\. Basic Operations

You can perform operations directly. The result is printed immediately.

```text
> A + B     
= {1, 2, 3, 4, 5}   (Union)

> A ^ B     
= {3}               (Intersection)

> A - B     
= {1, 2}            (Difference)

> A x B     
= {(1,3), (1,4), (1,5), (2,3)...} (Cartesian Product)
```

### 3\. Conditional Logic (If-Else)

The calculator supports `if-else` blocks with uppercase `DO` and `ELSE` keywords.

```text
> IF (A != B) DO A + B ELSE A ^ B
= {1, 2, 3, 4, 5}
```

### 4\. Exiting

Type `exit` or `quit` to close the program and clean up memory.

```text
> exit
```

-----

## 📂 Project Structure

  * **`lexer.l`** - Flex definition file. Tokenizes input (numbers, keywords, operators).
  * **`parser.y`** - Bison grammar file. Defines language rules, precedence, and AST logic.
  * **`set.c` / `set.h`** - Core C library implementing the Set data structures and mathematical logic.
  * **`main.c`** - Entry point. Initializes the parser.
  * **`sets_test.c`** - A test file for verifying the core logic of the Set library (set.c) without the parser. It manually runs unit tests for initialization, memory management, and set operations.
  * **`CMakeLists.txt`** - Build configuration script.

