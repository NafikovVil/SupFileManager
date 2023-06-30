#pragma once

#include "./event_subscription_simple_impl.hpp"
#include "./i_event_subscription_impl.hpp"

#include <memory>

namespace event::system
{
class EventSystem;

template< typename TEvent >
std::shared_ptr< IEventSubscriptionImpl >
GetEventSubscriptionImpl( std::function< void( TEvent const& ) > event_callback )
{
   return std::make_shared< EventSubscriptionImpl< TEvent > >( event_callback );
}
} // namespace event::system