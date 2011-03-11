; Alpha Loader
; Version 0.11
; -------------------------------------------------------
; Copyright (c) 2011, Robert Schofield and Matthew Carey
; All rights reserved.

[BITS 16]
[ORG 0x7C00]

start: JMP BootMain
; BPB Information

                        TIMES 0Bh-$+start DB 0
BytesPerSector:  	DW 512
SectorsPerCluster: 	DB 1
ReservedSectors: 	DW 1
NumberOfFATs: 	    DB 2
RootEntries: 	    DW 224
TotalSectors: 	    DW 2880
Media: 	            DB 0xF0
SectorsPerFAT: 	    DW 9
SectorsPerTrack: 	DW 18
HeadsPerCylinder: 	DW 2
HiddenSectors: 	    DD 0
TotalSectorsBig:     DD 0
DriveNumber: 	        DB 0
Unused: 	            DB 0
ExtBootSignature: 	DB 0x29
SerialNumber:	        DD 0x00000000
VolumeLabel: 	        DB "AlphaOS     "
FileSystem: 	        DB "FAT12   "

; Bootoader Main
; This loads into the second stage bootloader, which loads
; protected mode, the A20 gate, and then the kernel.



BootMain:
  XOR AX, AX
  MOV DS, AX
  MOV ES, AX
  MOV SS, AX
  MOV SP, 0x7C00
  MOV [DriveNumber], DL
  MOV AX, 03                       ; Clears the screen
  INT 10h                          
  MOV SI, Welcome                  ; Prints welcome text
  CALL PrintString

KeyBoardHandle:
  MOV AH, 00h
  INT 16h
  CMP AL, 0Dh
  JZ EnterKeyPressed
  CALL KeyBoardHandle

EnterKeyPressed:
  MOV SI, Boot
  CALL PrintString
;  CLI
;  XOR AX, AX
;  MOV DS, AX
;  LGDT [GDTDESC]
;  MOV EAX, CR0
;  OR EAX,1
;  MOV CR0,EAX
;  JMP $

PrintString:
  next_character:
    MOV AL, [SI]
    INC SI
    OR AL, AL
    JZ ExitFunction
    CALL PrintChar
    JMP next_character

PrintChar:
  MOV AH, 0x0E
  MOV BH, 00
  MOV BL, 05
  INT 10h
  RET

ExitFunction:
  RET

Welcome db 'Alpha Loader v0.12',13,10,'Created by: Robert Schofield and Matthew Carey',13,10,13,10,'Press enter key to load kernel...',13,10,0
Boot db 'Booting into the kernel...',13,10,0

TIMES 510-$+start DB 0
DB 055h, 0AAh