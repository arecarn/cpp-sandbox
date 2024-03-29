#include <PersistenceMock.hpp>
#include <TimeMock.hpp>
#include <TodoApp.hpp>

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

// startup
// read from log to rebuild list

// empty_todo_list
// add a todo, adds it to a list
// added todo default to unchecked
class GivenAEmptyList : public testing::Test
{
protected:
    void SetUp() override
    {
        m_app = std::make_unique<TodoApp>(m_time_mock, m_storage_mock);
    }

    std::unique_ptr<TodoApp> m_app;
    TimeMock m_time_mock;
    PersistenceMock m_storage_mock;
};

TEST_F(GivenAEmptyList, add_adds_an_unchecked_todo_to_the_list)
{
    std::string todo_text {"some todo text"};
    m_app->add(todo_text);
    auto list {m_app->list()};
    ASSERT_EQ(list[0].text(), todo_text);
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list[0].state(), Todo::State::Unchecked);
}
