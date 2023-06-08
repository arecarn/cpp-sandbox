#ifndef TODO_APP_HPP
#define TODO_APP_HPP

#include <StorageIntf.hpp>
#include <TimeIntf.hpp>
#include <Todo.hpp>
#include <TodoList.hpp>
#include <vector>

class TodoApp
{
public:
    TodoApp(
        TimeIntf& time,
        StorageIntf& storage)
        : m_time {time}
        , m_storage {storage}
    {
    }

    void add(const std::string& todo);
    void remove(TodoList::iterator itr);
    [[nodiscard]] const TodoList& list();

private:
    TimeIntf& m_time;
    StorageIntf& m_storage;
    TodoList m_list;
};

#endif // header guard
