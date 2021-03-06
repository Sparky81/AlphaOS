CC=gcc
OBJECTS=build/objects/*.o
SOURCES=src/main.c src/core.c src/text.c src/gdt.c src/idt.c src/isrs.c src/irq.c src/pit.c src/paging.c src/memory.c
EXECUTABLE=build/Kernel.bin
CFLAGS= -fno-stack-protector -fomit-frame-pointer -nostdlib -nostdin -I$(IDIR) -O2
LDFLAGS=-Tsrc/link.ld -melf_i386
ASFLAGS=-felf
IDIR=src/include
OBJDIR=build/objects
SAY=echo

all:
	@mkdir -p build
	@mkdir -p build/objects
	@$(SAY) "\033[1mCompiling Kernel...\033[0m"
	@gcc -m32 -c src/main.c $(C_FLAGS) -o $(OBJDIR)/main.o
	@gcc -m32 -c src/core.c $(C_FLAGS) -o $(OBJDIR)/core.o
	@gcc -m32 -c src/text.c $(C_FLAGS) -o $(OBJDIR)/text.o
	@gcc -m32 -c src/gdt.c $(C_FLAGS) -o $(OBJDIR)/gdt.o
	@gcc -m32 -c src/idt.c $(C_FLAGS) -o  $(OBJDIR)/idt.o
	@gcc -m32 -c src/isrs.c $(C_FLAGS) -o $(OBJDIR)/isrs.o
	@gcc -m32 -c src/irq.c $(C_FLAGS) -o $(OBJDIR)/irq.o
	@gcc -m32 -c src/pit.c $(C_FLAGS) -o $(OBJDIR)/pit.o
	@gcc -m32 -c src/malloc.c $(C_FLAGS) -o $(OBJDIR)/malloc.o
	@gcc -m32 -c src/paging.c $(C_FLAGS) -o $(OBJDIR)/paging.o
	@gcc -m32 -c src/keyboard.c $(C_FLAGS) -o $(OBJDIR)/kb.o
	@gcc -m32 -c src/time.c $(C_FLAGS) -o $(OBJDIR)/time.o
	@gcc -m32 -c src/memory.c $(C_FLAGS) -o $(OBJDIR)/memory.o
	@nasm $(ASFLAGS) src/boot.asm -o $(OBJDIR)/boot.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(OBJECTS)
	@$(SAY) "\033[1mDone!\033[0m"

debug:
	@mkdir -p build
	@mkdir -p build/objects
	@$(SAY) "\033[1mCompiling Kernel...\033[0m"
	@gcc -m32 -c src/main.c -Wall $(C_FLAGS) -o $(OBJDIR)/main.o
	@gcc -m32 -c src/core.c -Wall $(C_FLAGS) -o $(OBJDIR)/core.o
	@gcc -m32 -c src/text.c -Wall $(C_FLAGS) -o $(OBJDIR)/text.o
	@gcc -m32 -c src/gdt.c -Wall $(C_FLAGS) -o $(OBJDIR)/gdt.o
	@gcc -m32 -c src/idt.c -Wall $(C_FLAGS) -o $(OBJDIR)/idt.o
	@gcc -m32 -c src/isrs.c -Wall $(C_FLAGS) -o $(OBJDIR)/isrs.o
	@gcc -m32 -c src/irq.c -Wall $(C_FLAGS) -o $(OBJDIR)/irq.o
	@gcc -m32 -c src/pit.c -Wall $(C_FLAGS) -o $(OBJDIR)/pit.o
	@gcc -m32 -c src/paging.c -Wall $(C_FLAGS) -o $(OBJDIR)/paging.o
	@gcc -m32 -c src/keyboard.c -Wall $(C_FLAGS) -o $(OBJDIR)/kb.o
	@gcc -m32 -c src/malloc.c -Wall $(C_FLAGS) -o $(OBJDIR)/malloc.o
	@nasm $(ASFLAGS) src/paging.asm -o $(OBJDIR)/pg.o
	@nasm $(ASFLAGS) src/boot.asm -o $(OBJDIR)/boot.o
	@ld $(LDFLAGS) -o build/Kernel.bin $(OBJECTS)
	@$(SAY) "\033[1mDone!\033[0m"

clean:
	@rm -rf build/
	@$(SAY) "\033[1mDone!\033[0m"
