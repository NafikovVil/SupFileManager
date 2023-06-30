#pragma once

#include <event-system/event-subscription/i_event_subscription.hpp>

#include "../../src/implementation/event-subscription/i_event_subscription_impl.hpp"
#include "../../src/implementation/event_subscription_list.hpp"

#include <mutex>
#include <string>
#include <unordered_map>

namespace event::system
{
class EventSystem final
{
public:
   template< typename TEvent, typename... TArgs >
   void Notify( TArgs&&... args ) noexcept
   {
      auto event_name = std::string{ typeid( TEvent ).name() };

      std::lock_guard locker{ mSubscriptionMutex };
      auto& subscription_list = GetSubscriptionCallbackList( event_name );
      subscription_list.NotifyAll< TEvent >( std::forward< TArgs >( args )... );
   }

   void Subscribe( IEventSubscription const& event_subscription ) noexcept
   {
      auto event_subscription_impl_ptr = event_subscription.GetImpl();
      auto event_name = event_subscription_impl_ptr->GetEventName();

      std::lock_guard locker{ mSubscriptionMutex };
      auto& subscription_list = GetSubscriptionCallbackList( event_name );
      subscription_list.AddSubscription( event_subscription_impl_ptr );
   }

   void Unsubscribe( IEventSubscription const& event_subscription ) noexcept
   {
      auto event_subscription_impl_ptr = event_subscription.GetImpl();
      auto event_name = event_subscription_impl_ptr->GetEventName();

      std::lock_guard locker{ mSubscriptionMutex };
      if( auto subscription_iter = mSubscriptionCallbackMap.find( event_name );
          subscription_iter != mSubscriptionCallbackMap.end() )
      {
         subscription_iter->second.DeleteSubscription( event_subscription_impl_ptr );
      }
   }

private:
   EventSubscriptionList& GetSubscriptionCallbackList( std::string const& event_name ) noexcept
   {
      auto subscription_iter = mSubscriptionCallbackMap.find( event_name );
      if( subscription_iter == mSubscriptionCallbackMap.end() )
      {
         subscription_iter = mSubscriptionCallbackMap.insert( { event_name, EventSubscriptionList{} } ).first;
      }
      return subscription_iter->second;
   }

private:
   std::mutex mSubscriptionMutex;
   std::unordered_map< std::string, EventSubscriptionList > mSubscriptionCallbackMap;
};
} // namespace event::system