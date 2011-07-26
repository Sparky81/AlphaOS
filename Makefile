CC=gcc
OBJECTS=build/objects/*.o
SOURCES=src/main.c src/core.c src/text.c
EXECUTABLE=build/Kernel.bin
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tsrc/link.ld -melf_i386
ASFLAGS=-felf
IDIR=src/include

all:
	@mkdir -p build
	@mkdir -p build/objects
	@echo "\033[1mCompiling Kernel...\033[0m"
	@gcc -m32 -c src/main.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/main.o
	@gcc -m32 -c src/core.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/core.o
	@gcc -m32 -c src/text.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/text.o
	@nasm $(ASFLAGS) src/boot.asm -o build/objects/boot.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(OBJECTS)
	@echo "\033[1mDone!\033[0m"

clean:
	@rm -rf build/
	@echo "\033[1mDone!\033[0m"