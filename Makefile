all: 
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin
	@echo "\033[1mDone!\033[0m"
	
boot:
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin

clean: 
	@rm build/*.bin
	@echo "\033[1mCleaning completed.\033[0m"
