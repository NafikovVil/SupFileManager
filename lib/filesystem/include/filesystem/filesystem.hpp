#pragma once

#include <filesystem>
#include <optional>
#include <vector>

namespace filesystem
{
using FilePath = std::filesystem::path;
using FileList = std::vector< FilePath >;

class Filesystem final
{
public:
   Filesystem() = delete;
   ~Filesystem() = delete;

   static std::optional< FilePath > GetWorkDir();
   static bool SetWorkDir( FilePath const& new_work_dir );
   static FileList GetFilesInDirectory( FilePath const& directory );
   static bool CheckPathIsDirectory( FilePath const& new_work_dir );
};

} // namespace filesystem