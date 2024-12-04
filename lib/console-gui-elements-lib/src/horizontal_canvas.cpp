#include <console-gui-elements-lib/horizontal_canvas.hpp>

#include "ftxui/component/component.hpp" // for MenuEntry, Renderer, Vertical

namespace console::gui::elements
{

using namespace ftxui;

Component HorizontalCanvas::GetRendered( ftxui::Components const& child_list )
{
   return Container::Horizontal( child_list, &mSelected );
}

} // namespace console::gui::elements
