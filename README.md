# A Propositional Logic Parser

This command-line program parses and evaluates propositional logic expressions.

Supported operators:

- AND: `&`
- OR: `|`
- NOT: `!`
- Implication: `->`
- Biconditional: `<->`

Operator precedence, from highest to lowest, is:

```text
() > ! > & > | > -> > <->
```

Variable names may contain letters, underscores, and numbers, but cannot start
with a number. Whitespace is ignored.

## Requirements

- C++17 compiler
- CMake 3.16 or newer
- CLI11 development headers (`CLI/CLI.hpp`)

On Debian or Ubuntu, CLI11 may be installed with:

```bash
sudo apt install libcli11-dev
```

## Build

Configure and build in a separate directory:

```bash
cmake -S . -B build
cmake --build build
```

The executable is created at `build/parser`.

## Usage

Print a truth table:

```bash
./build/parser print "A & B"
```

Evaluate a proposition interactively:

```bash
./build/parser evaluate "A -> B"
```

Compare two propositions for logical equivalence:

```bash
./build/parser compare "A & B" "B & A"
```

The comparison command evaluates both propositions for every assignment of
their combined variables. Truth-table generation and comparison support at
most 20 distinct variables.
