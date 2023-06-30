#pragma once

#include <filesystem/filesystem.h>

namespace sup_manager
{
struct WorkspaceModel
{
   filesystem::FilePath mCurrentPath;
};
} // namespace sup_manager