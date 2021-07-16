#include "timer.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <thread>

Timer::Timer()
{
    last_time = glfwGetTime();
    start_time = last_time;
}

void Timer::update()
{
    float current_time = glfwGetTime();
    delta_time = current_time - last_time;
    last_time = current_time;
}

float Timer::frame()
{
    return delta_time;
}

float Timer::frombegin()
{
    return last_time - start_time;
}

void Timer::makeFrameRate(int frame_rate)
{
    int time_difference = 1000.f / frame_rate - delta_time;
    if (time_difference > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds((int) (time_difference)));
    }
}

void Timer::sleep(float seconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds((int) (1000 * seconds)));
}
