#pragma once

#include <ftxui/component/component_base.hpp>

#include <string>
#include <vector>

namespace console::gui::elements
{

class VerticalList
{
public:
   ftxui::Component GetRendered( std::vector< std::string > const& element_values_list );

private:
   ftxui::Components mMenuEntryList;
   int mSelected = 0;
};

} // namespace console::gui::elements