all: 
	@mkdir -p build
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin
	
	
boot:
	@mkdir -p build
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin

kernel:
	@echo "\033[1mCompiling Kernel...\033[0m"
	@gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o build/objects/main.o src/kernel/main.c
	@nasm -f aout -o build/objects/start.o src/kernel/start.asm
	@ld -T link.ld -o build/kernel.bin build/objects/start.o
	@echo "\033[1mDone!\033[0m"

clean: 
	@rm build/*.bin
	@echo "\033[1mCleaning completed.\033[0m"
