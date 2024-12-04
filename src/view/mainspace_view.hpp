#pragma once

#include "../include/i_view.hpp"
#include "../model/mainspace_model.hpp"

#include <console-gui-elements-lib/horizontal_canvas.hpp>

namespace sup_manager
{

// Нужен подумать как view будет получать обновление о изменении
class MainspaceView : public IView
{
public:
   MainspaceView( MainspaceModel& mainspace_model ) noexcept
      : mMainspaceModel( mainspace_model )
   {
   }

   MainspaceView( MainspaceView const& copy ) noexcept
      : mMainspaceModel( copy.mMainspaceModel )
   {
   }

   ftxui::Component GetComponent() const noexcept override
   {
      // FIXME: redudant copy
      ftxui::Components components;
      for( auto const& filespace : mMainspaceModel.mFilespaceViews )
      {
         components.push_back( filespace.get().GetComponent() );
      }

      return mFilespaceCanvas.GetRendered( components );
      /*vbox( {
                   rendered_element->Render() | size( HEIGHT, LESS_THAN, 10 ),
                   rendered_element->Render() | size( HEIGHT, LESS_THAN, 10 ),
                } ) |
                border;*/
   }

private:
   // FIXME: add const, need change copy constructor
   MainspaceModel mMainspaceModel;
   mutable console::gui::elements::HorizontalCanvas mFilespaceCanvas;
};

} // namespace sup_manager