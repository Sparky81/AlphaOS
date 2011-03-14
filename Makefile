all: 
	@mkdir -p build
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin
	
	
boot:
	@mkdir -p build
	@echo "\033[1mCompiling Bootloader...\033[0m"
	@nasm src/boot/boot.asm -o build/boot.bin

kernel:
	@mkdir -p build
	@mkdir -p build/objects
	@echo "\033[1mCompiling Kernel...\033[0m"
	@g++ -c src/kernel/kernel.cpp -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -o build/objects/Kernel.o
	@g++ -c src/kernel/Video.cpp -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -o build/objects/Video.o
	@nasm -f elf src/kernel/kernel_start.asm -o build/objects/Loader.o
	@ld -T src/kernel/link.ld -o build/Kernel.bin build/objects/Loader.o build/objects/Kernel.o build/objects/Video.o 
	@echo "\033[1mDone!\033[0m"
clean: 
	@rm build/*.bin
	@echo "\033[1mCleaning completed.\033[0m"
