#include "./main_workspace_controller.hpp"

#include <generic-core/logger.hpp>

namespace sup_manager
{

MainWorkspaceController::MainWorkspaceController( filesystem::FilePath const& initial_filepath,
                                                  uint8_t filespace_count ) noexcept
{
   for( auto i = 0; i < filespace_count; ++i )
   {
      mFilespaceControllersList.push_back( FilespaceController( initial_filepath ) );
   }

   for( auto& filespace_controllers : mFilespaceControllersList )
   {
      mMainspaceModel.mFilespaceViews.push_back( filespace_controllers.GetView() );
   }

   mMainspaceViewPtr = std::make_unique< MainspaceView >( mMainspaceModel );

   mActiveFilespaceController = mFilespaceControllersList.begin();
}

IView const& MainWorkspaceController::GetView() noexcept
{
   return *mMainspaceViewPtr;
}

} // namespace sup_manager