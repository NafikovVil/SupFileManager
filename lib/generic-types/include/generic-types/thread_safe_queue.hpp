#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>

namespace generic::types
{
    template <typename T>
    class ThreadSafeQueue
    {
        struct QueueNode
        {
            T mValue;
            std::unique_ptr<QueueNode> mNextNode;
        };

    public:
        ThreadSafeQueue() noexcept
            : mHead(std::make_unique<QueueNode>()), mTail(mHead.get())
        {
        }

        void Push(T value) noexcept
        {
            UpdateTail(std::forward<T>(value));
            mDataAvailableConditional.notify_one();
        }

        T Pop() noexcept
        {
            auto head_locker = WaitData();
            auto ex_head = PopHead();
            return ex_head->mValue;
        }

        bool Empty() noexcept
        {
            std::lock_guard head_locker(mHeadMutex);
            return mHead.get() == GetTail();
        }

    private:
        void UpdateTail(T &&value) noexcept
        {
            auto new_node = std::make_unique<QueueNode>();
            {
                std::lock_guard locker{mTailMutex};
                mTail->mValue = std::forward<T>(value);
                mTail->mNextNode = std::move(new_node);
                mTail = mTail->mNextNode.get();
            }
        }

        [[nodiscard]] std::unique_lock<std::mutex> WaitData() noexcept
        {
            std::unique_lock head_locker(mHeadMutex);
            mDataAvailableConditional.wait(head_locker, [this]
                                           { return mHead.get() != GetTail(); });
            return std::move(head_locker);
        }

        [[nodiscard]] std::unique_ptr<QueueNode> PopHead() noexcept
        {
            auto ex_head = std::move(mHead);
            mHead = std::move(ex_head->mNextNode);
            return ex_head;
        }

        [[nodiscard]] QueueNode *GetTail() noexcept
        {
            std::lock_guard locker{mTailMutex};
            return mTail;
        }

        std::mutex mHeadMutex;
        std::unique_ptr<QueueNode> mHead{};

        std::mutex mTailMutex;
        QueueNode *mTail{nullptr};

        std::condition_variable mDataAvailableConditional;
    };
}