#ifndef STORAGE_INTF_HPP
#define STORAGE_INTF_HPP

#include <TodoList.hpp>
#include <string>
#include <vector>

class PersistenceIntf
{
public:
    virtual void write(const TodoList& todo_list) = 0;
    virtual TodoList read() = 0;
    virtual ~PersistenceIntf() = default;
};

#endif // header guard
