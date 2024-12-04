#include "filespace_controller.hpp"

#include <console-gui-elements-lib/vertical_list.hpp>
#include <generic-core/logger.hpp>

namespace sup_manager
{

FilespaceController::FilespaceController( filesystem::FilePath const& initial_filepath ) noexcept
   : mModel{ initial_filepath,
             GetCurrentDirFilesName( filesystem::Filesystem::GetFilesInDirectory( initial_filepath ) ) }
   , mFilespaceView{ mModel }
{
}

FilespaceController::FilespaceController( FilespaceController const& copy ) noexcept
   : mModel( copy.mModel )
   , mFilespaceView( mModel )
{
}

IView const& FilespaceController::GetView() noexcept
{
   return mFilespaceView;
}

std::vector< std::string > FilespaceController::GetCurrentDirFilesName( filesystem::FileList const& filelist ) noexcept
{
   std::vector< std::string > res;

   for( auto const& file : filelist )
   {
      res.push_back( file.filename().string() );
   }

   return res;
}

} // namespace sup_manager