#pragma once

#include <ftxui/component/component_base.hpp>

#include <string>
#include <vector>

namespace console::gui::elements
{

class Window
{
public:
   ftxui::Component GetRendered( std::string const& title, ftxui::Component const& child );

private:
   std::string mTitle;
   ftxui::Component mChild;
};

} // namespace console::gui::elements