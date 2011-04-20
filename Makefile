SOURCES=build/objects/boot.o build/objects/main.o build/objects/video.o build/objects/common.o build/objects/gdt.o build/objects/descriptor_tables.o build/objects/isr.o build/objects/interrupt.o build/objects/timer.o 

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
	#@gcc -m32 -c src/kernel/hal/gdt.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/gdt.o
	#@gcc -m32 -c src/kernel/hal/idt.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/idt.o
	@gcc -m32 -c src/kernel/hal/descriptor_tables.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/descriptor_tables.o
	@gcc -m32 -c src/kernel/hal/isr.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/isr.o
	@gcc -m32 -c src/kernel/hal/timer.c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -o build/objects/timer.o
	@nasm $(ASFLAGS) src/kernel/kernel_start.asm -o build/objects/boot.o
	@nasm $(ASFLAGS) src/kernel/hal/gdt.s -o build/objects/gdt.o
	@nasm $(ASFLAGS) src/kernel/hal/interrupt.s -o build/objects/interrupt.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(SOURCES)
	@echo "\033[1mDone!\033[0m"

clean:
	@rm -rf build/
	@echo "\033[1mDone!\033[0m"
