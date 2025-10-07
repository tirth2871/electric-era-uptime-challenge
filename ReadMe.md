
---

## Design Approach

### 1. State Machine Architecture

The program uses a **state machine** to organize execution:

| State        | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `INIT`       | Initial setup; prints info messages.                                        |
| `PARSE`      | Parses the input file into station → charger → availability mappings.       |
| `CALCULATE`  | Merges intervals and computes uptime per station.                           |
| `PRINT`      | Prints the results to `stdout` in ascending order of station IDs.           |
| `ERROR`      | Prints `ERROR` if the input file is invalid or missing.                     |
| `EXIT`       | Ends execution gracefully.                                                  |

**Benefits**:

- Modular and maintainable
- Easy to add new stages (e.g., logging, advanced validation)
- Makes error handling consistent

---

### 2. Input Parsing

- Stations and charger IDs are read from `[Stations]` section.
- Charger availability reports are read from `[Charger Availability Reports]`.
- Each report contains:  
  `<Charger ID> <start time nanos> <end time nanos> <up (true/false)>`
- The program maps each charger to its station and collects all availability intervals.

---

### 3. Uptime Computation

For each station:

1. Collect all **uptime intervals** from all chargers.
2. Merge **overlapping intervals** to avoid double-counting.
3. Compute:

\[
\text{Uptime\%} = \left\lfloor \frac{\text{Total Uptime}}{\text{Total Reporting Window}} \times 100 \right\rfloor
\]

- Gaps in reports count as downtime.
- Rounds down to nearest integer.

---

### 4. Build Instructions

#### Requirements

- Linux environment (amd64)
- `g++` compiler (supports C++11 or higher)
- `make`

#### Steps

1. Clone or copy the project

```bash
git clone https://github.com/tirth2871/electric-era-uptime-challenge.git
```

2. In project root, run:

```bash
make
```
This will compile the program and generate the binary uptime.

### 5. Execution

1. To run the preloaded test cases, run:

```bash
make test
```

2. To run a custom test case apart from preloaded test cases, run:

```bash
./uptime "path to input.txt file"
```

Example:

```bash
./uptime tests/input_3.txt
```