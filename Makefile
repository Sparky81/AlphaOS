CC=gcc
OBJECTS=build/objects/*.o
SOURCES=src/main.c src/core.c src/text.c src/gdt.c src/idt.c src/isrs.c src/irq.c
EXECUTABLE=build/Kernel.bin
CFLAGS=-m32 -fomit-frame-pointer -nostdlib -nostdinc -fno-builtin -fno-stack-protector -I$(IDIR)
LDFLAGS=-Tsrc/link.ld -melf_i386
ASFLAGS=-felf
IDIR=src/include
OBJDIR=build/objects
SAY=echo -e

all:
	@mkdir -p build
	@mkdir -p build/objects
	@$(SAY) "\033[1mCompiling Kernel...\033[0m"
	@gcc -c src/main.c $(C_FLAGS) -o $(OBJDIR)/main.o
	@gcc -c src/core.c $(C_FLAGS) -o $(OBJDIR)/core.o
	@gcc -c src/text.c $(C_FLAGS) -o $(OBJDIR)/text.o
	@gcc -c src/gdt.c $(C_FLAGS) -o $(OBJDIR)/gdt.o
	@gcc -c src/idt.c $(C_FLAGS) -o  $(OBJDIR)/idt.o
	@gcc -c src/isrs.c $(C_FLAGS) -o $(OBJDIR)/isrs.o
	@gcc -c src/irq.c $(C_FLAGS) -o $(OBJDIR)/irq.o
	@nasm $(ASFLAGS) src/boot.asm -o $(OBJDIR)/boot.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(OBJECTS)
	@$(SAY) "\033[1mDone!\033[0m"

debug:
	@mkdir -p build
	@mkdir -p build/objects
	@$(SAY) "\033[1mCompiling Kernel...\033[0m"
	@gcc -c src/main.c -Wall $(C_FLAGS) -o $(OBJDIR)/main.o
	@gcc -c src/core.c -Wall $(C_FLAGS) -o $(OBJDIR)/core.o
	@gcc -c src/text.c -Wall $(C_FLAGS) -o $(OBJDIR)/text.o
	@gcc -c src/gdt.c -Wall $(C_FLAGS) -o $(OBJDIR)/gdt.o
	@gcc -c src/idt.c -Wall $(C_FLAGS) -o $(OBJDIR)/idt.o
	@gcc -c src/isrs.c -Wall $(C_FLAGS) -o $(OBJDIR)/isrs.o
	@gcc -c srs/irq.c -Wall $(C_FLAGS) -o $(OBJDIR)/irq.o
	@nasm $(ASFLAGS) src/boot.asm -o $(OBJDIR)/boot.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(OBJECTS)
	@$(SAY) "\033[1mDone!\033[0m"

clean:
	@rm -rf build/
	@$(SAY) "\033[1mDone!\033[0m"
