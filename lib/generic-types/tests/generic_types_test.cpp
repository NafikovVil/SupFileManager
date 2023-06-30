#include <generic-types/thread_safe_queue.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <future>
#include <optional>
#include <thread>

TEST(GenericTypesTest, PushAndPopSingleThread)
{
    generic::types::ThreadSafeQueue<int> queue;
    queue.Push(1);
    int x = 4;
    queue.Push(x);

    int first_pop = queue.Pop();
    int second_pop = queue.Pop();

    ASSERT_TRUE(first_pop == 1);
    ASSERT_TRUE(second_pop == 4);
    ASSERT_TRUE(queue.Empty());
}

void PushInQueueTask (generic::types::ThreadSafeQueue<int>& queue, int value, std::optional<uint32_t> sleep_millisecond = {})
{
    if (sleep_millisecond)
    {
        std::chrono::milliseconds milliseconds{*sleep_millisecond};
        std::this_thread::sleep_for(milliseconds);
    } 
    queue.Push(value); 
}

TEST(GenericTypesTest, PushAndPopTwoThread)
{
    constexpr int checked_val = 5;
    generic::types::ThreadSafeQueue<int> queue;
    auto task = std::async(
        std::launch::async, [&queue]
        { 
            PushInQueueTask(queue, checked_val, 500);
        });

    int pop = queue.Pop();
    task.wait();

    ASSERT_TRUE(pop == checked_val);
    ASSERT_TRUE(queue.Empty());
}
