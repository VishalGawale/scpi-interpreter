# scpi-interpreter

A small SCPI / IEEE 488.2 command interpreter in modern C++17.

This is a **learning project**. I'm a backend engineer (Python, C#) getting
hands-on with C++ and the command → function → instrument-state pattern used in
instrument control. It uses only generic, public SCPI commands.

**Status: work in progress.** The project builds and the test suite exists, but
the parser and interpreter are still being written, so some tests currently fail.

## Planned commands

| Line       | Behaviour                                  |
|------------|--------------------------------------------|
| `*IDN?`    | Return the identity string                 |
| `*RST`     | Reset frequency and power to defaults      |
| `FREQ <n>` | Set frequency in Hz (plain number)         |
| `FREQ?`    | Query the current frequency                |
| `POW <n>`  | Set power in dBm (plain number)            |
| `POW?`     | Query the current power                    |

## Build and test

Requires a C++17 compiler (g++ or clang++) and CMake 3.20 or newer.

```
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/scpi
```

## Design

Three small parts, each with one job:

- **Parser**: turns one text line into a `Command` (header, query flag, arguments).
- **Instrument**: holds the state (frequency, power) and a `reset()`.
- **Interpreter**: dispatches a parsed command, reads or writes the instrument
  state and returns the response.
