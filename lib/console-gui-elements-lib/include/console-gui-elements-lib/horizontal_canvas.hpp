#pragma once

#include <ftxui/component/component_base.hpp>

#include <string>
#include <vector>

namespace console::gui::elements
{

class HorizontalCanvas
{
public:
   ftxui::Component GetRendered( ftxui::Components const& child_list );

private:
   ftxui::Components mChildList;
   int mSelected = 0;
};

} // namespace console::gui::elements