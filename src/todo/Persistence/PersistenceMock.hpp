#ifndef STORAGE_MOCK_HPP
#define STORAGE_MOCK_HPP

#include "PersistenceIntf.hpp"
#include <gmock/gmock.h>

class PersistenceMock : public PersistenceIntf
{
public:
    MOCK_METHOD(void, write, (const TodoList& list), (override));
    MOCK_METHOD(TodoList, read, (), (override));
};

#endif // header guard
