#include <TodoApp.hpp>

void TodoApp::add(const std::string& todo)
{
    m_list.emplace_back(todo, m_time.now());
    m_storage.write(m_list); // TODO(replace m_storage with a repository)
}

void TodoApp::remove(TodoList::iterator itr)
{
    m_list.erase(itr);
}

const TodoList& TodoApp::list()
{
    return m_list;
}
