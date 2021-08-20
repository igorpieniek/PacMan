#include "Timer.h"
#include <iostream>

Timer& Timer::instance(){
    static Timer tim;
    return tim;
}

void Timer::addPeriodElapsedCallback(std::function<void()> fun, double sec){
    updateTime();
    callbacks.push_back({ fun, sec, currentTime, false });
}

void Timer::reset(){
    callbacks.clear();
}

Timer::Timer(){
    updateTime();
    thrd = std::thread(&Timer::process, this);
    thrd.detach();
}

void Timer::process(){
    while (1) {
        updateTime();
        executeCallbacks();
        deleteUsedCallbacks();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}

void Timer::deleteUsedCallbacks(){
    auto itersToRemove = std::remove_if(callbacks.begin(),
        callbacks.end(),
        [](const CallbackElement& cb) { return cb.isUsed; });
    
    callbacks.erase(itersToRemove, callbacks.end());
}

void Timer::executeCallbacks(){
    for (auto& cb : callbacks) {
        std::chrono::duration<double> elapsed_seconds = currentTime - cb.startTime;
        if (elapsed_seconds.count() >= cb.requiredTime) {
            cb.fun();
            cb.isUsed = true;
        }
    }
}

void Timer::updateTime(){
    currentTime = std::chrono::system_clock::now();
}
