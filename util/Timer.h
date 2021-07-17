//
// Created by Andrei García on 8/12/20.
//

#ifndef PROYECTO_PRINCIPAL_MODIFIED_TIMER_H
#define PROYECTO_PRINCIPAL_MODIFIED_TIMER_H

class Timer {
public:
    long currentMillis() {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        long nanos = duration_cast<nanoseconds>(now.time_since_epoch()).count();
        return nanos;
    }
};

#endif //PROYECTO_PRINCIPAL_MODIFIED_TIMER_H
