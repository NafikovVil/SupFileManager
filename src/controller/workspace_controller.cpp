#include "workspace_controller.hpp"

#include <console-gui-elements-lib/menu_list.hpp>
#include <filesystem/filesystem.h>
#include <generic-core/logger.hpp>

namespace sup_manager
{
WorkspaceController::WorkspaceController( filesystem::FilePath const& initial_filepath )
   : mModel{ initial_filepath }
{
   console::gui::elements::MenuList panel;
}
} // namespace sup_manager