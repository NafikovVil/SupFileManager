#pragma once

#include "../../../src/implementation/event-subscription/i_event_subscription_impl.hpp"

#include <memory>

namespace event::system
{
class EventSystem;

class IEventSubscription
{
   friend class EventSystem;

public:
   virtual ~IEventSubscription() = default;

   virtual void Subscribe() noexcept = 0;
   virtual void Unsubscribe() noexcept = 0;

private:
   virtual std::shared_ptr< IEventSubscriptionImpl > const GetImpl() const = 0;
};
} // namespace event::system