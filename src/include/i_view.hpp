#pragma once

#include <ftxui/component/component_base.hpp>

namespace sup_manager
{

class IView
{
public:
   // FIXME: Добавить const
   virtual ftxui::Component GetComponent() const noexcept = 0;
};

} // namespace sup_manager