	# @echo "\033[1mCompiling Kernel...\033[0m"
	# @nasm -f aout src/kernel/kernel_start.asm -o build/objects/ks.o
	# @gcc -c src/kernel/kernel.c -o build/objects/kernel.o
	# @ld -T src/kernel/link.ld -o build/kernel.bin build/objects/ks.o build/objects/kernel.o

all: 
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin
	
boot:
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin

clean: 
	@rm build/*.bin
	@rm build/objects/*
	@echo "\033[1mCleaning completed.\033[0m"
