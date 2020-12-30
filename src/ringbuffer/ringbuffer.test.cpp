#include "ringbuffer.hpp"
#include "gtest/gtest.h"

TEST(ringbuffer, push_back)
{
    ringbuffer<int, 3> rb;

    ASSERT_EQ(rb.capacity(), 3);
    ASSERT_EQ(rb.size(), 0);

    ASSERT_EQ(true, rb.push_back(1));
    ASSERT_EQ(rb.size(), 1);

    ASSERT_EQ(true, rb.push_back(2));
    ASSERT_EQ(rb.size(), 2);

    ASSERT_EQ(true, rb.push_back(3));
    ASSERT_EQ(rb.size(), 3);

    ASSERT_EQ(1, rb[0]);
    ASSERT_EQ(2, rb[1]);
    ASSERT_EQ(3, rb[2]);

    ASSERT_EQ(false, rb.push_back(4));
    ASSERT_EQ(rb.size(), 3);
}

TEST(ringbuffer, push_front)
{
    ringbuffer<int, 3> rb;

    ASSERT_EQ(rb.capacity(), 3);
    ASSERT_EQ(rb.size(), 0);

    ASSERT_EQ(true, rb.push_front(1));
    ASSERT_EQ(rb.size(), 1);

    ASSERT_EQ(true, rb.push_front(2));
    ASSERT_EQ(rb.size(), 2);

    ASSERT_EQ(true, rb.push_front(3));
    ASSERT_EQ(rb.size(), 3);

    ASSERT_EQ(3, rb[0]);
    ASSERT_EQ(2, rb[1]);
    ASSERT_EQ(1, rb[2]);

    ASSERT_EQ(false, rb.push_front(4));
    ASSERT_EQ(rb.size(), 3);
}

TEST(ringbuffer, pop_front)
{
    ringbuffer<int, 3> rb;
    rb.push_back(1);
    rb.push_back(2);
    rb.push_back(3);

    ASSERT_EQ(true, rb.pop_front());
    ASSERT_EQ(2, rb[0]);
    ASSERT_EQ(3, rb[1]);
    ASSERT_EQ(rb.size(), 2);

    ASSERT_EQ(true, rb.pop_front());
    ASSERT_EQ(3, rb[0]);
    ASSERT_EQ(rb.size(), 1);

    ASSERT_EQ(true, rb.pop_front());
    ASSERT_EQ(rb.size(), 0);
}

TEST(ringbuffer, pop_back)
{
    ringbuffer<int, 3> rb;
    rb.push_back(1);
    rb.push_back(2);
    rb.push_back(3);

    ASSERT_EQ(true, rb.pop_back());
    ASSERT_EQ(1, rb[0]);
    ASSERT_EQ(2, rb[1]);
    ASSERT_EQ(rb.size(), 2);

    ASSERT_EQ(true, rb.pop_back());
    ASSERT_EQ(1, rb[0]);
    ASSERT_EQ(rb.size(), 1);

    ASSERT_EQ(true, rb.pop_back());
    ASSERT_EQ(rb.size(), 0);
}

TEST(ringbuffer, push_back_wrap)
{
    ringbuffer<int, 3> rb;
    rb.push_back(1);
    rb.push_back(2);
    rb.push_back(3);

    // push_back wraps around to front
    rb.pop_front();
    rb.push_back(4);
    ASSERT_EQ(2, rb[0]);
    ASSERT_EQ(3, rb[1]);
    ASSERT_EQ(4, rb[2]);

    rb.pop_front();
    ASSERT_EQ(3, rb[0]);
    ASSERT_EQ(4, rb[1]);

    // pop_front wraps around to the front
    rb.pop_front();
    ASSERT_EQ(4, rb[0]);

    rb.pop_front();
    ASSERT_TRUE(rb.empty());
}

TEST(ringbuffer, push_front_wrap)
{
    ringbuffer<int, 3> rb;
    rb.push_front(1);
    rb.push_front(2);
    rb.push_front(3);

    // push_back wraps around to front
    rb.pop_front();
    rb.push_front(4);
    ASSERT_EQ(4, rb[0]);
    ASSERT_EQ(2, rb[1]);
    ASSERT_EQ(1, rb[2]);

    rb.pop_front();
    ASSERT_EQ(2, rb[0]);
    ASSERT_EQ(1, rb[1]);

    // pop_front wraps around to the front
    rb.pop_front();
    ASSERT_EQ(1, rb[0]);

    rb.pop_front();
    ASSERT_TRUE(rb.empty());
}
