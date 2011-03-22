SOURCES=build/objects/boot.o build/objects/main.o build/objects/video.o build/objects/common.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tsrc/kernel/link.ld -melf_i386
ASFLAGS=-felf

all:
	
kernel:
	@mkdir -p build
	@mkdir -p build/objects
	@echo "\033[1mCompiling Kernel...\033[0m"
	@gcc -m32 -c src/kernel/main.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/main.o
	@gcc -m32 -c src/kernel/common.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/common.o
	@gcc -m32 -c src/kernel/video.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/video.o
	@nasm $(ASFLAGS) src/kernel/kernel_start.asm -o build/objects/boot.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(SOURCES)
	@echo "\033[1mDone!\033[0m"

clean:
	@rm -rf build/
	@echo "\033[1mDone!\033[0m"