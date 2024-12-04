#include <filesystem/filesystem.hpp>
#include <generic-core/logger.hpp>
#include <generic-core/logger_init.hpp>

#include "./controller/main_workspace_controller.hpp"

#include "./render/render_processor.hpp"

int main( int argc, char* argv[] )
{
   using namespace sup_manager;
   generic::core::SetupLogger( "SupManager" );

   LOG_WRITE_INFO( "SupManager start %v", 12 );

   auto work_dir = filesystem::Filesystem::GetWorkDir();
   if( !work_dir )
   {
      LOG_WRITE_ERROR( "main fail: work_dir is nullopt" );
      return -1;
   }

   LOG_WRITE_INFO( "controller" );
   MainWorkspaceController controller{ *work_dir };

   LOG_WRITE_INFO( "render" );
   RenderProcessor render_processor{ controller };

   LOG_WRITE_INFO( "start" );
   render_processor.Render();

   return 0;
}
