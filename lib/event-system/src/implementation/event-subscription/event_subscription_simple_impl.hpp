#pragma once

#include "./i_event_subscription_impl.hpp"

#include <generic-core/logger.hpp>

#include <functional>
#include <mutex>
#include <string>

namespace event::system
{
namespace
{
static EventSubscriptionId SUBSCRIPTION_ID_NUM = 0;

struct EventSubscriptionSequentionalID
{
   static EventSubscriptionId GetId() noexcept
   {
      static std::mutex subscription_mutex;
      std::lock_guard locker{ subscription_mutex };
      return SUBSCRIPTION_ID_NUM++;
   }
};
} // namespace

template< typename TEvent >
class EventSubscriptionImpl final : public IEventSubscriptionImpl
{
public:
   EventSubscriptionImpl( std::function< void( TEvent const& ) > event_callback ) noexcept
      : mEventName( std::string{ typeid( TEvent ).name() } )
      , mEventCallback( event_callback )
   {
   }

   EventSubscriptionImpl( EventSubscriptionImpl const& clone ) = delete;
   EventSubscriptionImpl& operator=( EventSubscriptionImpl const& clone ) = delete;

   std::string const& GetEventName() const noexcept override
   {
      return mEventName;
   }

   uint64_t GetId() const noexcept override
   {
      return mSubscriptionId;
   }

   void Notify( TEvent const& event ) const noexcept
   {
      try
      {
         mEventCallback( event );
      }
      catch( std::exception const& except )
      {
         LOG_WRITE_ERROR( "EventSubscriptionImpl: catch exception: %v", except.what() );
      }
      catch( ... )
      {
         LOG_WRITE_ERROR( "EventSubscriptionImpl: unknown error" );
      }
   }

private:
   std::string mEventName;
   std::function< void( TEvent const& ) > mEventCallback;
   EventSubscriptionId mSubscriptionId = EventSubscriptionSequentionalID::GetId();
};
} // namespace event::system