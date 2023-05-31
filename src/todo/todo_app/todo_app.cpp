#include <todo_app.hpp>

// TodoApp {
//     void add(std::string todo);
//     void check(Todo& todo);
//     void uncheck(Todo& todo);
//     const std::vector<Todo>& get_list();

//     private:
//     std::vector<Todo> m_list;
// };
//
void TodoApp::add(const std::string& todo)
{
    m_list.emplace_back(todo);
}

void TodoApp::check(Todo& todo)
{
}

void TodoApp::uncheck(Todo& todo)
{
}

const std::vector<Todo>& TodoApp::list()
{
    return m_list;
}
