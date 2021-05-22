
#ifndef _TADTimer
#define _TADTimer

#include <iostream>
using namespace std;

#include <time.h>

struct Timer
{
    int tiempoInicio, tiempoFin;
};

Timer timer(int t1, int t2)
{
    Timer y = {t1, t2};
    return {y};
}

void timerStart(Timer *t)
{

    time_t time1 = time(NULL);
}

void timerStop(Timer *t)
{

    time_t time2 = time(NULL);
}

unsigned long long timerElapsedTime(Timer t)
{

    return (time1 - time2);
}

#endif

/* 

struct Timer
{
  unsigned long long start;
  unsigned long long end;
};

Timer timer()
{
   return {};
}

void timerStart(Timer& t)
{
    t.start = std::chrono::system_clock::now().time_since_epoch() /
          std::chrono::milliseconds(1);;
}

void timerStop(Timer& t)
{
   t.end = std::chrono::system_clock::now().time_since_epoch() /
         std::chrono::milliseconds(1);;
}

unsigned long long timerElapsedTime(Timer t)
{

   return (t.end-t.start);
}

*/