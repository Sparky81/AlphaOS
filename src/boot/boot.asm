; Alpha Loader
; Version 0.11
; -------------------------------------------------------
; Copyright (c) 2011, Robert Schofield and Matthew Carey
; All rights reserved.

[BITS 16]
[ORG 0x7C00]

start: JMP BootMain

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

BootMain:
  XOR AX, AX

TIMES 510-$+start DB 0
DB 055h, 0AAh