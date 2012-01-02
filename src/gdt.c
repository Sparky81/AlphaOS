#define SEG_TYPE(x) ((x) << 0x04) // 0 for system, 1 for code/data
#define SEG_PRES(x) ((x) << 0x07) // Present
#define SEG_SAVL(x) ((x) << 0x0C) // Availible for system use
#define SEG_LONG(x) ((x) << 0x0D) // Long Mode
#define SEG_SIZE(x) ((x) << 0x0E) // Size 0:16bt 1:32bt
#define SEG_GRAN(x) ((x) << 0x0F) // Granularity 0:1B 1:4kb-4gb
#define SED_PRIV(x) ((x) << 0x03) // Set privilege level, 1-3

#define SEG_DATA_RD        0x00
#define SEG_DATA_RDA       0x01
#define SEG_DATA_RDWR      0x02
#define SEG_DATA_RDWRA     0x03
#define SEG_DATA_RDEXPD    0x04
#define SEG_DATA_RDEXPDA   0x05
#define SEG_DATA_RDWREXPD  0x06
#define SEG_DATA_RDWREXPDA 0x07
#define SEG_CODE_EX        0x08
#define SEG_CODE_EXA       0x09
#define SEG_CODE_EXRD      0x0A
#define SEG_CODE_EXRDA     0x0B
#define SEG_CODE_EXC       0x0C
#define SEG_CODE_EXCA      0x0D
#define SEG_CODE_EXRDC     0x0E
#define SEG_CODE_EXRDCA    0x0F

#define GDT_CODE_PL0 SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_CODE_EXRD
#define GDT_DATA_PL0 SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_DATA_RDWR

#define GDT_DATA_PL3 SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_DATA_RDWR
#define GDT_CODE_PL3 SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_CODE_EXRD

void create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
  uint64_t descriptor;
  
  // Create high 32 bit segment
  descriptor  =  limit       & 0x000F0000;
  descriptor |= (flag <<  8) & 0x00F0FF00;
  descriptor |= (base << 16) & 0xFF0000FF;

  // Shift by 32 to allow for low segment
  descriptor <<= 32;

  // Low segment
  descriptor |= base  << 16;
  descriptor |= limit  & 0x0000FFFF;
}

void encodeGdtEntry(uint8_t *target, struct GDT source)
{
    // Check the limit to make sure that it can be encoded
    if ((source.limit > 65536) && (source.limit & 0xFFF) != 0xFFF)) {
        error("Cannot encode GDT Entry.");
    }
    if (source.limit > 65536) {
        // Adjust granularity if required
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    } else {
        target[6] = 0x40;
    }
 
    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0xF;
 
    // Encode the base 
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
 
    // And... Type
    target[5] = source.type;
}
