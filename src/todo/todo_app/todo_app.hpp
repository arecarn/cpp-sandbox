#ifndef TODO_APP_HPP
#define TODO_APP_HPP

#include <todo.hpp>
#include <vector>

class TodoApp
{
public:
    void add(const std::string& todo);
    void check(Todo& todo);
    void uncheck(Todo& todo);
    [[nodiscard]] const std::vector<Todo>& list();

private:
    std::vector<Todo> m_list;
};

#endif // header guard
