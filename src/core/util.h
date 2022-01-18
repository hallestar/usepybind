#ifndef TRYPYBIND_UTIL_H
#define TRYPYBIND_UTIL_H

#include <chrono>
#include <string>

#define CHRONO std::chrono

class StopWatch {

public:
    StopWatch() : start_(CHRONO::steady_clock::now()) {
    }

    ~StopWatch() {
    }

    template<typename Duration>
    Duration Elapse() const {
        auto now = CHRONO::steady_clock::now();
        auto delta = now - start_;
        return CHRONO::duration_cast<Duration>(delta);
    }

    CHRONO::milliseconds ElapseMills() const {
        return Elapse<CHRONO::milliseconds>();
    }

private:
    CHRONO::time_point<CHRONO::steady_clock> start_;
};

class Counter {
public:
    Counter(const char *counter_name)
            : name_(counter_name),
              cnt_(0) {
    }

    void Increment() {
        cnt_;
    }

    inline uint32_t GetCount() const {
        return cnt_;
    }

private:
    std::string name_;
    uint32_t cnt_;
};

#endif //TRYPYBIND_UTIL_H
