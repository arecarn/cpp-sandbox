#include <TodoList.hpp>
#include <string>
#include <vector>

#ifndef STORAGE_INTF_HPP
#define STORAGE_INTF_HPP

class StorageIntf
{
public:
    virtual void write(const TodoList& todo_list) = 0;
    virtual TodoList read() = 0;
};

#endif // header guard
