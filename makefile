.PHONY: test

hack-asm: hack-asm.c utils/helper.c utils/table.c
	mkdir -p build
	gcc -Wall -Wextra hack-asm.c utils/helper.c utils/table.c -o build/hack-asm

test: hack-asm
	./tests/run-tests.sh --no-build
