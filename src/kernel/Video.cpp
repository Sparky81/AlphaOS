#include "includes/Video.h"

Video::Video()
{
    pos=0;	off=0;
    videomem = (unsigned short*) 0xb8000;  
}

Video::~Video() {}

void Video::clear()
{
    unsigned int i;
    for(i=0; i<(100*45); i++)
    {
	videomem[i] = (unsigned char)' '|0x0700;  
    }
    pos=0; off=0;
}

void Video::write(char *cp)
{
    char * str = cp, *ch;
 
    for(ch = str; *ch; ch++)
    {
	put(*ch); 
    }
}

void Video::put(char c)
{
    if (c == '\n')
    {
	pos=0xB8000;
    }
    if (pos>=120)
    {
	pos=0;
	off += 80;
    };
    if (off>=(100*45))
    {
	clear(); 
    };
    videomem[off + pos] = (unsigned char)c|0x0700;
    pos++;
}
