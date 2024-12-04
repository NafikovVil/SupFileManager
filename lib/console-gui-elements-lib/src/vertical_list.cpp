#include <console-gui-elements-lib/vertical_list.hpp>

#include "ftxui/component/component.hpp" // for MenuEntry, Renderer, Vertical
#include "ftxui/screen/color.hpp"        // for Color, Color::Blue, Color::Cyan, Color::Green, Color::Red, Color::Yellow

namespace console::gui::elements
{

using namespace ftxui;

MenuEntryOption Colored( ftxui::Color c )
{
   MenuEntryOption option;
   option.transform = [ c ]( EntryState state )
   {
      state.label = ( state.active ? "> " : "  " ) + state.label;
      Element e = text( state.label ) | color( c );
      if( state.focused )
         e = e | inverted;
      if( state.active )
         e = e | bold;
      return e;
   };
   return option;
}

Component VerticalList::GetRendered( std::vector< std::string > const& element_values_list )
{
   for( auto const& element_value : element_values_list )
   {
      mMenuEntryList.push_back( MenuEntry( element_value ) );
   }

   return Container::Vertical( std::move( mMenuEntryList ), &mSelected );
}

} // namespace console::gui::elements
