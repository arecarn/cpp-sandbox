#include "Mailbox.hpp"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <random>

TEST(mailbox, test)
{
    Mailbox<int> m;
    int limit {10000};

    std::thread writer([&] {

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

        int to_write = 0;
        while (to_write != limit)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(dist6(rng)));
            ++to_write;
            std::cerr << "writing value:" << to_write << '\n'
                      << std::flush;
            m.push(to_write);
        }
    });

    std::thread reader([&] {
        int last_read = 0;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

        while (last_read != limit)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(dist6(rng)));
            int value;
            if (m.try_pop(value))
            {
                ASSERT_GT(value, last_read);
                last_read = value;
            }
            else
            {
            }
        }
    });

    writer.join();
    reader.join();
}
