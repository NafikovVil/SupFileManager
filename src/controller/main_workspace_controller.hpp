#pragma once

#include "../include/i_controller.hpp"
#include "../model/mainspace_model.hpp"
#include "../view/mainspace_view.hpp"
#include "./filespace_controller.hpp"

#include <filesystem/filesystem.hpp>

#include <vector>

namespace sup_manager
{

class MainWorkspaceController : public IController
{
public:
   MainWorkspaceController( filesystem::FilePath const& initial_filepath, uint8_t filespace_count = 2 ) noexcept;

   IView const& GetView() noexcept override;

private:
   using FilespaceControllerList = std::vector< FilespaceController >;
   FilespaceControllerList mFilespaceControllersList;
   FilespaceControllerList::iterator mActiveFilespaceController;
   MainspaceModel mMainspaceModel;
   std::unique_ptr< MainspaceView > mMainspaceViewPtr;
};

} // namespace sup_manager