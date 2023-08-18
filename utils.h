#include <stdarg.h>


void note(const char *fmt, ...);
void info(const char *fmt, ...);
void warn(const char *fmt, ...);
void write_line(const char *fmt, ...);
void die(const char *fmt);


#define in() {note("Calling => %s",__func__);}
#define out() {note("Returing <= %s",__func__);}
#define FOR(number) for (unsigned long i = 0; i < number; i++)
