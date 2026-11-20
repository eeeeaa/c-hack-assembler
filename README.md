// More details: ~/Documents/ObsidianNotes/Learning/Coursera/nand2tetris/Assembler
// Phase 1: Basic assembler without symbol and label handling
// Phase 2: Develop symbol handling
// Phase 3: integrate both systems, build a general Hack assembler

// Pseudocode
// input: hack asm file (.asm)
// output: hack machine code binary file (.hack)
// START LOOP:
// Read next line of asm file
// break each line into array of chars
// loop over chars, map to tokens
// get arrays of tokens
// loop over each token
// lookup symbol-opcode map table
// get array of binaries
// concat array of binaries into instruction
// update hack file
// end of file? -> exit loop
// END LOOP

