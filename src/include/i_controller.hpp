#pragma once

#include "./i_view.hpp"

namespace sup_manager
{

class IController
{
public:
   // TODO: add const
   virtual IView const& GetView() noexcept = 0;
};

} // namespace sup_manager