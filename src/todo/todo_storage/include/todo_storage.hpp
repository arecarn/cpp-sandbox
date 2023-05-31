#include <string>
#include <todo_app.hpp>
#include <vector>

class ITodoStorage
{
public:
    virtual write_list(std::vector<Todo> list) = 0;
    virtual std::vector<Todo> read_list() = 0;
};
