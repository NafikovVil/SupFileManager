#include <event-system/event-subscription/event_subscription.hpp>
#include <event-system/event_system.hpp>

#include <gtest/gtest.h>

struct TestEvent
{
};

struct TestEventWithArg
{
   int32_t x{ 0 };
};

TEST( EventsystemTest, CreateEventSubscription )
{
   using namespace event::system;
   EventSystem event_system;
   EventSubscription< TestEvent > subscription{ event_system, []( auto const& ) {} };
   event_system.Subscribe( subscription );

   ASSERT_TRUE( true );
}

TEST( EventsystemTest, Emit )
{
   bool expected{ false };

   using namespace event::system;
   EventSystem event_system;
   EventSubscription< TestEvent > subscription{ event_system, [ &expected ]( auto const& )
                                                {
                                                   expected = true;
                                                } };
   event_system.Subscribe( subscription );
   event_system.Notify< TestEvent >();

   ASSERT_TRUE( expected );
}

TEST( EventsystemTest, RemoveSubscription )
{
   bool expected{ false };

   using namespace event::system;
   EventSystem event_system;
   EventSubscription< TestEvent > subscription{ event_system, [ &expected ]( auto const& )
                                                {
                                                   expected = true;
                                                } };
   event_system.Subscribe( subscription );

   subscription.Unsubscribe();
   event_system.Notify< TestEvent >();

   ASSERT_FALSE( expected );
}

TEST( EventsystemTest, EmitWithArg )
{
   int32_t expected{ 0 };

   using namespace event::system;
   EventSystem event_system;
   EventSubscription< TestEventWithArg > subscription{ event_system, [ &expected ]( auto const& event )
                                                       {
                                                          expected = event.x;
                                                       } };
   event_system.Subscribe( subscription );

   event_system.Notify< TestEventWithArg >( 2 );

   ASSERT_TRUE( expected == 2 );
}

TEST( EventsystemTest, ManySubscribe )
{
   bool first_expected{ false };
   int32_t second_expected{ 0 };

   using namespace event::system;
   EventSystem event_system;

   EventSubscription< TestEvent > first_subscribe{ event_system, [ &first_expected ]( auto const& )
                                                   {
                                                      first_expected = true;
                                                   } };
   event_system.Subscribe( first_subscribe );

   EventSubscription< TestEvent > second_subscribe{ event_system, [ &second_expected ]( auto const& )
                                                    {
                                                       second_expected = 1;
                                                    } };
   event_system.Subscribe( second_subscribe );

   event_system.Notify< TestEvent >();

   ASSERT_TRUE( first_expected );
   std::cout << first_expected << std::endl;
   ASSERT_TRUE( second_expected == 1 );
   std::cout << second_expected << std::endl;
}

TEST( EventsystemTest, EmitException )
{
   bool expected{ false };

   using namespace event::system;
   EventSystem event_system;
   EventSubscription< TestEvent > subscription{ event_system, [ &expected ]( auto const& )
                                                {
                                                   throw std::runtime_error( "Exception in callback" );
                                                   expected = true;
                                                } };
   event_system.Subscribe( subscription );
   event_system.Notify< TestEvent >();

   ASSERT_FALSE( expected );
}
