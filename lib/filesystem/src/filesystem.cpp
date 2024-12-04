#include <filesystem/filesystem.hpp>

#include <generic-core/logger.hpp>

// std::filesystem
#include <filesystem>

namespace filesystem
{

namespace fs = std::filesystem;

std::optional< FilePath > Filesystem::GetWorkDir()
{
   std::error_code error_code;
   auto workdir_path = fs::current_path( error_code );
   if( error_code )
   {
      LOG_WRITE_ERROR( "Filesystem Error in GetWorkDir(): %v", error_code.message() );
      return {};
   }
   return workdir_path;
}

bool Filesystem::SetWorkDir( FilePath const& new_work_dir )
{
   if( !CheckPathIsDirectory( new_work_dir ) )
   {
      LOG_WRITE_ERROR( "Filesystem Error in SetWorkDir(): %v is not directory", new_work_dir.string() );
      return false;
   }

   std::error_code error_code;
   fs::current_path( new_work_dir, error_code );
   if( error_code )
   {
      LOG_WRITE_ERROR( "Filesystem Error in SetWorkDir(): %v", error_code.message() );
      return false;
   }
   return true;
}

FileList Filesystem::GetFilesInDirectory( FilePath const& directory )
{
   std::error_code error_code;
   FileList res;
   for( auto const& entry : fs::directory_iterator( directory, error_code ) )
   {
      if( error_code )
      {
         LOG_WRITE_ERROR( "Filesystem Error in GetFilesInDirectory(): %v", error_code.message() );
         continue;
      }
      res.emplace_back( entry.path() );
   }
   return res;
}

bool Filesystem::CheckPathIsDirectory( FilePath const& new_work_dir )
{
   std::error_code error_code;
   auto is_directory = !fs::is_directory( new_work_dir, error_code );
   if( error_code )
   {
      LOG_WRITE_ERROR( "Filesystem Error in CheckPathIsDirectory(): %v", error_code.message() );
      return false;
   }
   return is_directory;
}
} // namespace filesystem