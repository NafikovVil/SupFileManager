#include "./render_processor.hpp"

#include <ftxui/component/captured_mouse.hpp>     // for ftxui
#include <ftxui/component/component.hpp>          // for MenuEntry, Renderer, Vertical
#include <ftxui/component/component_base.hpp>     // for ComponentBase
#include <ftxui/component/component_options.hpp>  // for MenuEntryOption
#include <ftxui/component/event.hpp>              // for Event
#include <ftxui/component/loop.hpp>               // for Loop
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp> // for operator|, Element, separator, text, hbox, size, frame, color, vbox, HEIGHT, LESS_THAN, bold, border, inverted
#include <ftxui/dom/node.hpp> // for Render

namespace sup_manager
{

using namespace ftxui;

RenderProcessor::RenderProcessor( IController& controller ) noexcept
   : mController{ controller }
{
}

void RenderProcessor::Render() noexcept
{
   auto screen = ScreenInteractive::TerminalOutput();

   auto const& view = mController.GetView();
   auto rendered_element = view.GetComponent();

   // Display together the menu with a border
   auto renderer = Renderer( rendered_element,
                             [ & ]
                             {
                                return vbox( {
                                          rendered_element->Render() | size( HEIGHT, LESS_THAN, 10 ),
                                       } ) |
                                       border;
                             } );

   renderer |= CatchEvent(
      [ & ]( Event ) -> bool
      {
         mEventCount++;
         return false;
      } );

   Loop loop( &screen, renderer );

   while( !loop.HasQuitted() )
   {
      mCustomLoopCount++;
      loop.RunOnce();
      std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
   }

   screen.Loop( renderer );
}

} // namespace sup_manager