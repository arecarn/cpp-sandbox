#ifndef TODO_APP_HPP
#define TODO_APP_HPP

#include <Todo.hpp>
#include <vector>

class TodoApp
{
public:
    void add(const std::string& todo);
    void remove(Todo& todo);
    [[nodiscard]] const std::vector<Todo>& list();

private:
    std::vector<Todo> m_list;
};

#endif // header guard
