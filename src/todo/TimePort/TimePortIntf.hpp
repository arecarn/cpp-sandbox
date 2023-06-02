#include <chrono>

class TimePortIntf
{
public:
    virtual time_t time() = 0;
};
