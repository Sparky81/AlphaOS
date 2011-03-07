; Alpha Loader
; Version 0.11
; -------------------------------------------------------
; Copyright (c) 2011, Robert Schofield and Matthew Carey
; All rights reserved.

[BITS 16]
[ORG 0x7C00]

start: JMP BootMain

                        TIMES 0Bh-$+start DB 0
bpbBytesPerSector:  	DW 512
bpbSectorsPerCluster: 	DB 1
bpbReservedSectors: 	DW 1
bpbNumberOfFATs: 	    DB 2
bpbRootEntries: 	    DW 224
bpbTotalSectors: 	    DW 2880
bpbMedia: 	            DB 0xF0
bpbSectorsPerFAT: 	    DW 9
bpbSectorsPerTrack: 	DW 18
bpbHeadsPerCylinder: 	DW 2
bpbHiddenSectors: 	    DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber: 	        DB 0
bsUnused: 	            DB 0
bsExtBootSignature: 	DB 0x29
bsSerialNumber:	        DD 0xa0a1a2a3
bsVolumeLabel: 	        DB "AlphaOS     "
bsFileSystem: 	        DB "FAT12   "

BootMain:
  MOV AX, 03                       ; Clears the screen
  INT 10h                          ; Screen interrupt.
  MOV SI, Welcome
  CALL PrintString
  CALL KeyBoardHandle

; 16 Bit Calls
KeyBoardHandle:
  MOV AH, 00h
  INT 16h
  CMP AL, 0Dh
  JZ EnterKeyPressed
  CALL KeyBoardHandle

EnterKeyPressed:
  CALL Loader

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

; Soon, the code below will load a kernel from a FAT12 Drive.
; --------------------------------------------------------------
Loader:
  MOV SI, Boot
  CALL PrintString

Welcome db 'Alpha Loader v0.11',13,10,'Created by: Robert Schofield and Matthew Carey',13,10,13,10,'Press the Enter Key to boot.',13,10,0
Boot db 'Booting into the kernel...',13,10,0

TIMES 510-$+start DB 0
DB 055h, 0AAh



