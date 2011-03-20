#ifndef VIDEO_H
#define VIDEO_H

class Video
{
public:
    Video();
    ~Video();
    void clear();
    void write(char *cp);
    void put(char c);
private:
    unsigned short *videomem;
    unsigned int off;
    unsigned int pos;
};

#endif