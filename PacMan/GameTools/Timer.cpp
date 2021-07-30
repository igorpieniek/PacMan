#include "Timer.h"

Timer& Timer::instance(){
    static Timer tim;
    return tim;
}

void Timer::addPeriodElapsedCallback(std::function<void()> fun, double sec){
    updateTime();
    callbacks.push_back({ fun, sec, last, false });
}

Timer::Timer(){
    updateTime();
    thrd = std::thread(&Timer::process, this);
    thrd.join();
}

void Timer::process(){
    updateTime();
    for (auto& cb : callbacks) {
        std::chrono::duration<double> elapsed_seconds = last - cb.startTime;
        if (elapsed_seconds.count() >= cb.requiredTime) {
            cb.fun();
            cb.isUsed = true;
        }
    }
    deleteUsedCallbacks();

}

void Timer::deleteUsedCallbacks(){
    auto itersToRemove = std::remove_if(callbacks.begin(),
        callbacks.end(),
        [](const CallbackElement& cb) { return cb.isUsed; });

    callbacks.erase(itersToRemove, callbacks.end());
}

void Timer::updateTime(){
    last = std::chrono::system_clock::now();
}
