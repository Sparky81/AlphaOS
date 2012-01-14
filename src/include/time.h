#ifndef TIME
#define TIME
typedef struct time_ {
  int sec;
  int min;
  int hour;
  int day;
  int month;
  int year;
} Time;

unsigned char readCMOS(unsigned char addr);

void writeCMOS(unsigned char addr, unsigned int val);

Time current_time(void);

#endif
