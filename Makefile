CC=gcc
OBJECTS=build/objects/*.o
SOURCES=src/main.c src/core.c src/text.c
EXECUTABLE=build/Kernel.bin
CFLAGS=-Wall -fomit-frame-pointer -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tsrc/link.ld -melf_i386
ASFLAGS=-felf
IDIR=src/include
SAY=echo -e

all:
	@mkdir -p build
	@mkdir -p build/objects
	@$(SAY) "\033[1mCompiling Kernel...\033[0m"
	@gcc -m32 -c src/main.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/main.o
	@gcc -m32 -c src/core.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/core.o
	@gcc -m32 -c src/text.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/text.o
	@nasm $(ASFLAGS) src/boot.asm -o build/objects/boot.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(OBJECTS)
	@$(SAY) "\033[1mDone!\033[0m"

clean:
	@rm -rf build/
	@$(SAY) "\033[1mDone!\033[0m"
