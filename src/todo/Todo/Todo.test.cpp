#include "Todo.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

class GivenANewTodo : public testing::Test
{
public:
    static const std::string Text;

protected:
    void SetUp() override
    {
        m_todo = std::make_unique<Todo>(Text, 0);
    }

    std::unique_ptr<Todo> m_todo;
};

const std::string GivenANewTodo::Text {"todo text"};

TEST_F(GivenANewTodo, its_text_is_given_by_the_constructor)
{
    ASSERT_EQ(m_todo->text(), GivenANewTodo::Text);
}

TEST_F(GivenANewTodo, its_is_unchecked)
{
    ASSERT_EQ(m_todo->state(), Todo::State::Unchecked);
}

TEST_F(GivenANewTodo, toggle_checks_it_and_toggle_again_uncheckes_it)
{
    m_todo->toggle();
    ASSERT_EQ(m_todo->state(), Todo::State::Checked);
    m_todo->toggle();
    ASSERT_EQ(m_todo->state(), Todo::State::Unchecked);
}

TEST_F(GivenANewTodo, text_can_be_changed)
{
    static const std::string New_Text {"new todo text"};
    m_todo->text(New_Text);
    ASSERT_EQ(m_todo->text(), New_Text);
}

TEST_F(GivenANewTodo, test_chrono)
{
    // auto start = std::chrono::system_clock::now();
    // std::time_t end_time = std::chrono::system_clock::to_time_t(start);
}
