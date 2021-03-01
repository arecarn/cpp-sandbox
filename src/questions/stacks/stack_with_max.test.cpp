// Design a stack that includes a max operation, in addition to push and pop.
// The max method should return the maximum value stored in the stack.

#include <gtest/gtest.h>
#include <numeric>
#include <stack>
#include <stdexcept>
#include <unordered_map>

class StackWithMax
{
public:
    void push(int val);
    void pop();
    int peek();
    int max();

private:
    std::stack<int> m_data;

    struct MaxWithCount
    {
        int max;
        size_t count;
    };
    std::stack<MaxWithCount> m_max_with_count;
};

void StackWithMax::push(int val)
{
    if (m_max_with_count.empty() || val > max())
    {
        m_max_with_count.push({val, 1});
    }
    else if (val == max())
    {
        m_max_with_count.top().count++;
    }

    m_data.push(val);
}

void StackWithMax::pop()
{
    if (m_data.empty())
    {
        throw std::out_of_range{"empty"};
    }

    if (m_data.top() == m_max_with_count.top().max)
    {
        if (m_max_with_count.top().count == 1)
        {
            m_max_with_count.pop();
        }
        else
        {
            m_max_with_count.top().count--;
        }
    }

    m_data.pop();
}

int StackWithMax::peek()
{
    if (m_data.empty())
    {
        throw std::out_of_range{"empty"};
    }
    return m_data.top();
}

int StackWithMax::max()
{
    if (m_data.empty())
    {
        throw std::out_of_range{"empty"};
    }
    return m_max_with_count.top().max;
}

template <typename Exception, typename Operation>
bool throws(Operation op)
{
    bool exception_caught = false;
    try
    {
        op();
    }
    catch (Exception&)
    {
        exception_caught = true;
    }
    catch (...)
    {
    }
    return exception_caught;
}

TEST(stack_with_max, test)
{
    StackWithMax s;
    s.push(1);
    ASSERT_EQ(s.max(), 1);

    s.push(3);
    ASSERT_EQ(s.max(), 3);

    s.push(2);
    ASSERT_EQ(s.max(), 3);

    s.pop(); // pop 2
    ASSERT_EQ(s.max(), 3);

    s.pop(); // pop 3
    ASSERT_EQ(s.max(), 1);

    s.pop(); // pop 1

    auto max_operation = [&s]() {
        s.max();
    };
    ASSERT_TRUE(throws<std::exception>(max_operation));

    auto pop_operation = [&s]() {
        s.pop();
    };
    ASSERT_TRUE(throws<std::exception>(pop_operation));
}
