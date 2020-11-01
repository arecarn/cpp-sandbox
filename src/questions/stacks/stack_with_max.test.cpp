// Design a stack that includes a max operation, in addition to push and pop.
// The max method should return the maximum value stored in the stack.

#include <gtest/gtest.h>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <vector>

class StackWithMax
{
public:
    void push(int val);
    void pop();
    int peek();
    int max();

private:
    std::vector<int> m_data;
    std::vector<int> m_max_data;
};

void StackWithMax::push(int val)
{
    m_data.push_back(val);
    if (m_max_data.empty() || val >= max())
    {
        m_max_data.push_back(val);
    }
}

void StackWithMax::pop()
{
    if (m_data.empty())
    {
        throw std::out_of_range {"empty"};
    }

    if (*m_data.rbegin() == *m_max_data.rbegin())
    {
        m_max_data.erase(m_max_data.begin() + (m_max_data.size() - 1));
    }
    m_data.erase(m_data.begin() + (m_data.size() - 1));
}

int StackWithMax::peek()
{
    if (m_data.empty())
    {
        throw std::out_of_range {"empty"};
    }
    return m_data[m_data.size() - 1];
}

int StackWithMax::max()
{

    if (m_data.empty())
    {
        throw std::out_of_range {"empty"};
    }
    return m_max_data[m_max_data.size() - 1];
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
