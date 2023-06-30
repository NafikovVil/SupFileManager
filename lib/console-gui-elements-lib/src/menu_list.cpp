#include <console-gui-elements-lib/menu_list.hpp>

#include <iostream>

#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for MenuEntry, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for MenuEntryOption
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/elements.hpp" // for operator|, Element, separator, text, hbox, size, frame, color, vbox, HEIGHT, LESS_THAN, bold, border, inverted
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::Green, Color::Red, Color::Yellow

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

MenuList::MenuList()
{
   int selected = 0;

   auto menu = Container::Vertical(
      {
         MenuEntry( " 1. improve" ),
         MenuEntry( " 2. tolerant" ),
         MenuEntry( " 3. career" ),
         MenuEntry( " 4. cast" ),
         MenuEntry( " 5. question" ),
      },
      &selected );

   // Display together the menu with a border
   auto renderer = Renderer( menu,
                             [ & ]
                             {
                                return vbox( {
                                          hbox( text( "selected = " ), text( std::to_string( selected ) ) ),
                                          separator(),
                                          menu->Render() | frame | size( HEIGHT, LESS_THAN, 10 ),
                                       } ) |
                                       border;
                             } );

   auto screen = ScreenInteractive::TerminalOutput();
   screen.Loop( renderer );
}
} // namespace console::gui::elements
