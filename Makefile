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
