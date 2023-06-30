#pragma once

#include <generic-types/i_controller.hpp>

#include "../model/workspace_model.hpp"

#include <memory>

namespace sup_manager
{
class WorkspaceController : public generic::types::IController
{
public:
   WorkspaceController( filesystem::FilePath const& initial_filepath );

private:
   WorkspaceModel mModel;
};
} // namespace sup_manager