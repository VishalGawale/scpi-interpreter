# scpi-interpreter

A small SCPI command interpreter written in modern C++17. It reads one text
line at a time, such as `FREQ 2000000` or `*IDN?`, changes or reads the state
of a simulated instrument, and prints the reply.

This is a learning project. I built it to get hands-on with C++ and with the
command -> function -> instrument state pattern used in instrument control.
It uses only generic, public SCPI / IEEE 488.2 conventions, and the instrument
is a simulation with no hardware behind it.

## Build and run

Needs g++ or clang++ and CMake 3.14 or newer.

```bash
cmake -S . -B build
cmake --build build
./build/scpi
```

Run the tests:

```bash
ctest --test-dir build --output-on-failure
```

Type `quit` or press Ctrl+D to leave the program.

## Supported commands

| Line | Type | Behaviour |
|------|------|-----------|
| `*IDN?` | query | Returns `SIM Instruments,SCPI-Sim,0,1.0` |
| `*RST` | set | Resets frequency to 1000000 Hz and power to 0 dBm |
| `FREQ <n>` | set | Stores the frequency in Hz (plain number) |
| `FREQ?` | query | Returns the stored frequency |
| `POW <n>` | set | Stores the power in dBm (plain number) |
| `POW?` | query | Returns the stored power |

Headers are case-insensitive (`freq?` works). Unknown commands return
`-113,"Undefined header"`. A missing or invalid number returns
`-104,"Data type error"` and leaves the state unchanged.

Example session:

```
*IDN?
SIM Instruments,SCPI-Sim,0,1.0
FREQ 2000000
FREQ?
2000000
FREQ 10abc
-104,"Data type error"
```

## Design

Three small pieces, each with one job:

1. **Parser** (`src/parser.cpp`): turns one line into a `Command` with a
   header, an `is_query` flag and a list of arguments.
2. **Instrument** (`src/instrument.cpp`): holds the state (`frequency_hz`,
   `power_dbm`) and a `reset()`.
3. **Interpreter** (`src/interpreter.cpp`): takes the parsed command,
   dispatches on the header, reads or writes the instrument and returns the
   reply text.

I split it this way so each part can be tested alone and so a new command
only touches the interpreter.

Tests use plain CTest and a small `check.h` helper, with no test framework.

## What I'd do next

- Units: accept `FREQ 100MHz` and `POW 20 dBm`.
- An error queue with `SYST:ERR?`.
- `*CLS` and `*OPC?`.
- One more subsystem, for example `OUTP ON|OFF`.
- Long and short header forms (`FREQuency` as well as `FREQ`).