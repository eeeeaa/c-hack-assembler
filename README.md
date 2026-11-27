# Note regarding AI usage
Implementation codes are handwritten for learning purposes following the course.

AI usage includes: documentation and README, debugging, tests, and test scripts.

# Hack Assembler (C)

An assembler for the Hack assembly language from [nand2tetris](https://www.nand2tetris.org/)
(project 6 of *The Elements of Computing Systems*).

It translates `.asm` files into 16-bit Hack machine code, one instruction per
line, handling labels, the pre-defined symbols (`SP`, `LCL`, `ARG`, `THIS`,
`THAT`, `R0`–`R15`, `SCREEN`, `KBD`), and user-defined variables.

## Build and run

```sh
make                                    # builds build/hack-asm
mkdir -p output                         # the assembler writes output/out.hack
./build/hack-asm path/to/program.asm
```

## Status

- Phase 1: Basic assembler without symbol and label handling
- Phase 2: Develop symbol handling
- Phase 3: integrate both systems, build a general Hack assembler

## Testing
Each test is a pair of files in `tests/`:

- `<name>.asm` — a Hack assembly program
- `<name>.hack` — the expected binary output, one 16-bit instruction per line

Run every test (builds the assembler first):

```sh
./tests/run-tests.sh
```

Other forms:

```sh
make test                    # same thing via make
./tests/run-tests.sh label   # only tests whose name contains "label"
./tests/run-tests.sh --no-build
```

The runner executes the assembler from the repository root (the assembler writes
to `output/out.hack`), diffs that file against `<name>.hack`, and exits non-zero
if any test fails. To add a test, add `<name>.asm` and its expected
`<name>.hack`; no script changes are needed.

`n2tetris-tests/` holds the official project-6 programs (Add, Max, Rect, Pong)
for end-to-end checks:

```sh
./n2tetris-tests/generate-hack.sh        # assemble all of them
```

## Pseudocode
input: hack asm file (.asm)
output: hack machine code binary file (.hack)

1. Initialization
	1. construct empty symbol table
	2. add pre-defined symbol to table
2. First pass
	1. scan entire program
	2. for each instruction
		1. if its match form `(XXX)`, add key-value pair to table
3. Second pass
	1. Set n to 16
	2. Scan entire program
	3. For each instruction
		1. if `@symbol`, lookup symbol in table
			1. if found, substitute that value in instruction
			2. if not found
				1. Add pair of symbol and n to symbol table
				2. use n to substitute the value in the instruction
				3. n++
		2. if its a C-instruction, complete the translation by looking up related tables
	4. Write translated instruction

## License

MIT — see [LICENSE](LICENSE).

The files under `n2tetris-tests/` (and `tests/max-test.asm`) come from the
nand2tetris course materials and are not covered by that license; see
[NOTICE](NOTICE).
