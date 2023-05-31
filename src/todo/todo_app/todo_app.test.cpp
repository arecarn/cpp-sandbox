#include <todo_app.hpp>

#include <memory>

#include <gtest/gtest.h>

// class UncheckedTodo : public testing::Test {
// };
// unchecked todo
// checking a unchecked todo put's it in the checked state
// unchecking a unchecked todo put's it in the unchecked state
//
// class CheckedTodo : public testing::Test {
// };
// checked todo
// checking a checked todo put's it in the checked state
// unchecking a checked todo put's it in the unchecked state

// empty_todo_list
// add a todo, adds it to a list
// added todo default to unchecked

// startup
// read from log to rebuild list
class EmptyTodoList : public testing::Test
{
protected:
    void SetUp() override
    {
        m_todo_app = std::make_unique<TodoApp>();
    }

    std::unique_ptr<TodoApp> m_todo_app;
};

TEST_F(EmptyTodoList, add_adds_a_todo_to_the_list)
{
    std::string todo_text {"some todo text"};
    m_todo_app->add(todo_text);
    auto list {m_todo_app->list()};
    ASSERT_EQ(list[0].text(), todo_text);
    ASSERT_EQ(list.size(), 1);
}
