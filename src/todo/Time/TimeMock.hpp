#ifndef TIME_MOCK_HPP
#define TIME_MOCK_HPP

#include "TimeIntf.hpp"
#include <gmock/gmock.h>

class TimeMock : public TimeIntf
{
public:
    MOCK_METHOD(time_t, now, (), (override));
};

#endif // header guard
