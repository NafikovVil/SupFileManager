#pragma once

#include <event-system/event-subscription/i_event_subscription.hpp>
#include <event-system/event_system.hpp>

#include "../../../src/implementation/event-subscription/event_subscription_fabric.hpp"
#include "../../../src/implementation/event-subscription/i_event_subscription_impl.hpp"

#include <functional>
#include <memory>

namespace event::system
{
template< typename TEvent >
class EventSubscription final : public IEventSubscription
{
public:
   // Better don't block on this callback. It can block thread where emit event
   // Data used in callback should destructed after EventSubscription
   EventSubscription( EventSystem& event_system, std::function< void( TEvent const& ) > event_callback ) noexcept
      : mEventSystem( event_system )
      , mImplPtr( GetEventSubscriptionImpl( event_callback ) )
   {
   }

   ~EventSubscription() noexcept
   {
      mEventSystem.Unsubscribe( *this );
   }

   EventSubscription( EventSubscription const& clone ) = delete;
   EventSubscription& operator=( EventSubscription const& clone ) = delete;

   void Subscribe() noexcept
   {
      mEventSystem.Subscribe( *this );
   }

   void Unsubscribe() noexcept
   {
      mEventSystem.Unsubscribe( *this );
   }

private:
   std::shared_ptr< IEventSubscriptionImpl > const GetImpl() const
   {
      return mImplPtr;
   }

private:
   EventSystem& mEventSystem;
   // shared_ptr for create weak_ptr that event_system use
   std::shared_ptr< IEventSubscriptionImpl > mImplPtr;
};
} // namespace event::system