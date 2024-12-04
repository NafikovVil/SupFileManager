#pragma once

#include "../include/i_view.hpp"
#include "../model/filespace_model.hpp"

#include <console-gui-elements-lib/vertical_list.hpp>
#include <console-gui-elements-lib/window.hpp>

namespace sup_manager
{

// Нужен подумать как view будет получать обновление о изменении
class FilespaceView : public IView
{
public:
   FilespaceView( FilespaceModel& filespace_model ) noexcept
      : mFilespaceModel( filespace_model )
   {
   }

   FilespaceView( FilespaceView const& copy ) noexcept
      : mFilespaceModel( copy.mFilespaceModel )
      , mVerticalList( copy.mVerticalList )
      , mWindow( copy.mWindow )
   {
   }

   ftxui::Component GetComponent() const noexcept override
   {
      return mWindow.GetRendered( mFilespaceModel.mCurrentPath.string(),
                                  mVerticalList.GetRendered( mFilespaceModel.mCurrentFiles ) );
   }

private:
   const FilespaceModel& mFilespaceModel;
   mutable console::gui::elements::VerticalList mVerticalList;
   mutable console::gui::elements::Window mWindow;
};

} // namespace sup_manager