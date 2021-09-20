#include "Timer.h"
#include <iostream>


Timer::Timer(){
    thrd = std::thread(&Timer::process, this);
    thrd.detach();
}

void Timer::startPeriodElapse(double duration){
    if (callback == nullptr) {
        std::cout << "Error: First set callback function" << std::endl;
        return;
    }

    if (!isWaiting) {
        requiredTime = duration;
        updateTime();
        startTime = currentTime;
        isWaiting = true;
    }
    else {
        std::cout << "Cannot start timer - already in process!" << std::endl;
    }
}

void Timer::setCallback(std::function<void()> fun){
    callback = fun;
}


void Timer::reset(){
    updateTime();
    startTime = currentTime;
    isWaiting = false;
}

void Timer::process(){
    while (1) {
        updateTime();
        executeCallback();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}


void Timer::executeCallback(){
    if (isWaiting) {
        std::chrono::duration<double> elapsed_seconds = currentTime - startTime;
        if (elapsed_seconds.count() >= requiredTime) {
            isWaiting = false;
            if(callback)callback();
        }
    }
}

void Timer::updateTime(){
    currentTime = std::chrono::system_clock::now();
}
