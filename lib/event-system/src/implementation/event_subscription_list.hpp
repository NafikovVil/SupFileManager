#pragma once

#include "./event-subscription/event_subscription_simple_impl.hpp"
#include "./event-subscription/i_event_subscription_impl.hpp"

#include <list>
#include <memory>

namespace event::system
{
class EventSubscriptionList final
{
public:
   void AddSubscription( std::shared_ptr< IEventSubscriptionImpl > const& subscription ) noexcept
   {
      mSubscriptionCallbackList.emplace_back( subscription->GetId(), subscription );
   }

   void DeleteSubscription( std::shared_ptr< IEventSubscriptionImpl > const& subscription ) noexcept
   {
      mSubscriptionCallbackList.remove_if(
         [ & ]( auto const& subscription_callback )
         {
            return subscription_callback.mSubscriptionId == subscription->GetId();
         } );
   }

   template< typename TEvent, typename... TArgs >
   void NotifyAll( TArgs&&... args ) noexcept
   {
      TEvent event{ std::forward< TArgs >( args )... };
      for( auto const& subscription_info : mSubscriptionCallbackList )
      {
         if( auto subscription_ptr = subscription_info.mSubscriptionPtr.lock(); subscription_ptr )
         {
            // AAAA FCK
            auto& subscription_impl = static_cast< EventSubscriptionImpl< TEvent >& >( *subscription_ptr );
            subscription_impl.Notify( event );
         }
      }
   }

private:
   struct SubscriptionInfo
   {
      EventSubscriptionId mSubscriptionId;
      std::weak_ptr< IEventSubscriptionImpl > mSubscriptionPtr;
   };

   std::list< SubscriptionInfo > mSubscriptionCallbackList;
};
} // namespace event::system