#pragma once

#include <filesystem/filesystem.hpp>

#include <string>
#include <vector>

namespace sup_manager
{

struct FilespaceModel
{
   filesystem::FilePath mCurrentPath;
   std::vector< std::string > mCurrentFiles;
};

} // namespace sup_manager