#include <generic-core/logger.hpp>

#include "controller/workspace_controller.hpp"


int main( int argc, char* argv[] )
{
   using namespace sup_manager;
   generic::core::SetupLogger( "SupManager" );

   LOG_WRITE_INFO( "SupManager start %v", 12 );

   WorkspaceController controller;
}
