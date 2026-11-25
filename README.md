## References
- More details: ~/Documents/ObsidianNotes/Learning/Coursera/nand2tetris/Assembler

- Phase 1: Basic assembler without symbol and label handling
- Phase 2: Develop symbol handling
- Phase 3: integrate both systems, build a general Hack assembler

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
		2. if its a C-instruction, complete the translation buy looking up related tables
	4. Write translated instruction

