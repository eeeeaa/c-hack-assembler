hack-asm: hack-asm.c utils/helper.c utils/table.c
	gcc -Wall -Wextra hack-asm.c utils/helper.c utils/table.c -o hack-asm