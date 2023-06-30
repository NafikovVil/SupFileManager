#pragma once

#include <cstdint>
#include <string>

namespace event::system
{
using EventSubscriptionId = uint64_t;

class IEventSubscriptionImpl
{
public:
   virtual ~IEventSubscriptionImpl() = default;

   virtual std::string const& GetEventName() const noexcept = 0;
   virtual uint64_t GetId() const noexcept = 0;
};
} // namespace event::system