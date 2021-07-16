#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>


class Timer
{
public:
    float start_time = 0.f;
    float delta_time = 0.f;
    float last_time  = 0.f;
public:
    Timer();
    void update();
    float frame();
    float frombegin();
    void makeFrameRate(int frame_rate);
    static void sleep(float seconds);
};
#endif // TIMER_H
