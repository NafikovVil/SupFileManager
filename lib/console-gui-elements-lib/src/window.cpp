#include <console-gui-elements-lib/window.hpp>

#include "ftxui/component/component.hpp" // for MenuEntry, Renderer, Vertical

namespace console::gui::elements
{

using namespace ftxui;

Component Window::GetRendered( std::string const& title, ftxui::Component const& child )
{
   mTitle = title;
   mChild = child;
   return Renderer( mChild,
                    [ this ]
                    {
                       return window( text( mTitle ), mChild->Render() );
                    } );
}

} // namespace console::gui::elements
