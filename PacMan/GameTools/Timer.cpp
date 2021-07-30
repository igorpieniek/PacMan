#include "Timer.h"

Timer& Timer::instance(){
    static Timer tim;
    return tim;
}
