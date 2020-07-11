#include "ringbuffer.hpp"
#include "gtest/gtest.h"

TEST(ringbuffer, push)
{
    ringbuffer<int, 3> rb;

    ASSERT_EQ(rb.capacity(), 3);
    ASSERT_EQ(rb.size(), 0);

    ASSERT_EQ(true, rb.push(1));
    ASSERT_EQ(rb.size(), 1);

    ASSERT_EQ(true, rb.push(2));
    ASSERT_EQ(rb.size(), 2);

    ASSERT_EQ(true, rb.push(3));
    ASSERT_EQ(rb.size(), 3);

    ASSERT_EQ(1, rb[0]);
    ASSERT_EQ(2, rb[1]);
    ASSERT_EQ(3, rb[2]);

    ASSERT_EQ(false, rb.push(4));
    ASSERT_EQ(rb.size(), 3);
}

TEST(ringbuffer, pop)
{
    ringbuffer<int, 3> rb;
    rb.push(1);
    rb.push(2);
    rb.push(3);

    ASSERT_EQ(true, rb.pop());
    ASSERT_EQ(2, rb[0]);
    ASSERT_EQ(3, rb[1]);
    ASSERT_EQ(rb.size(), 2);

    ASSERT_EQ(true, rb.pop());
    ASSERT_EQ(3, rb[0]);
    ASSERT_EQ(rb.size(), 1);

    ASSERT_EQ(true, rb.pop());
    ASSERT_EQ(rb.size(), 0);
}

TEST(ringbuffer, push_wrap)
{
    ringbuffer<int, 3> rb;
    rb.push(1);
    rb.push(2);
    rb.push(3);

    // push wraps around to front
    rb.pop();
    rb.push(4);
    ASSERT_EQ(2, rb[0]);
    ASSERT_EQ(3, rb[1]);
    ASSERT_EQ(4, rb[2]);

    rb.pop();
    ASSERT_EQ(3, rb[0]);
    ASSERT_EQ(4, rb[1]);

    // pop wraps around to the front
    rb.pop();
    ASSERT_EQ(4, rb[0]);

    rb.pop();
    ASSERT_TRUE(rb.empty());
}
