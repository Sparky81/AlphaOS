;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;	 ____	  	  __	         __________    __        __          ______     ;;;;;;;;;;
;;;;;;;;;      /  __  \          |  |           |  _____   |  |  |      |  |        /  __  \    ;;;;;;;;;;
;;;;;;;;;     /  /  \  \         |  |           |  |____|  |  |  |______|  |       /  /  \  \   ;;;;;;;;;;
;;;;;;;;;    /  /____\  \        |  |           |    ______/  |   ______   |      /  /____\  \  ;;;;;;;;;;
;;;;;;;;;   /  /      \  \       |  |_______    |   |         |  |      |  |     /  /      \  \ ;;;;;;;;;;
;;;;;;;;;  /__/        \__\      |__________|   |___|         |__|      |__|    /__/        \__\;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[BITS 32]

[global start]
[extern k_main] ; this is in the c file

MODULEALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .text 
align 4
MultiBootHeader:
  dd MAGIC
  dd FLAGS
  dd CHECKSUM

STACKSIZE equ 0x4000

start:
  MOV ESP, stack+STACKSIZE
  PUSH EAX
  PUSH EBX

  CALL k_main
  CLI

Hang:
  JMP Hang

section .bss
align 4
stack: 
  resb STACKSIZE