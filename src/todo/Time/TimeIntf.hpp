#ifndef TIME_INF_HPP
#define TIME_INF_HPP

#include <chrono>

class TimeIntf
{
public:
    virtual time_t now() = 0;
    virtual ~TimeIntf() = default;
};

#endif // header guard
