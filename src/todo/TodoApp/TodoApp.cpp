#include <TodoApp.hpp>

void TodoApp::add(const std::string& todo)
{
    m_list.emplace_back(todo, 0); // TODO add time port
}

void TodoApp::remove(Todo& todo)
{
}

const std::vector<Todo>& TodoApp::list()
{
    return m_list;
}
