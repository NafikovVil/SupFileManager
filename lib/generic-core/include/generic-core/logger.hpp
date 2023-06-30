#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#pragma GCC diagnostic ignored "-Wconversion"
#include <easylogging++.h>
#pragma GCC diagnostic pop

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

INITIALIZE_EASYLOGGINGPP

// Simple and stupid logger implementation
namespace generic::core
{

namespace
{
std::string GetFilename( std::string const& application_name )
{
   std::time_t rawtime;
   std::time( &rawtime );
   auto* timeinfo = std::localtime( &rawtime );

   char buffer[ 80 ];
   std::strftime( buffer, 80, "%Y-%m-%d-%H-%M-%S", timeinfo );

   // TODO: Target directory is hardcode, need change
   return "C:\\wrk\\log\\" + application_name + "-" + std::string{ buffer } + ".txt";
}
} // namespace

static el::Logger* LOGGER_PTR{ nullptr };

#define LOG_WRITE_DEBUG( format, ... )                                                                                 \
   generic::core::LOGGER_PTR != nullptr ? generic::core::LOGGER_PTR->debug( format, ##__VA_ARGS__ )                    \
                                        : ( void )( std::cerr << format << std::endl );

#define LOG_WRITE_TRACE( format, ... )                                                                                 \
   generic::core::LOGGER_PTR != nullptr ? generic::core::LOGGER_PTR->trace( format, ##__VA_ARGS__ )                    \
                                        : ( void )( std::cerr << format << std::endl );

#define LOG_WRITE_INFO( format, ... )                                                                                  \
   generic::core::LOGGER_PTR != nullptr ? generic::core::LOGGER_PTR->info( format, ##__VA_ARGS__ )                     \
                                        : ( void )( std::cerr << format << std::endl );

#define LOG_WRITE_WARNING( format, ... )                                                                               \
   generic::core::LOGGER_PTR != nullptr ? generic::core::LOGGER_PTR->warn( format, ##__VA_ARGS__ )                     \
                                        : ( void )( std::cerr << format << std::endl );

#define LOG_WRITE_ERROR( format, ... )                                                                                 \
   generic::core::LOGGER_PTR != nullptr ? generic::core::LOGGER_PTR->error( format, ##__VA_ARGS__ )                    \
                                        : ( void )( std::cerr << format << std::endl );

void SetupLogger( std::string const& application_name )
{
   el::Configurations defaultConf;

   defaultConf.setToDefault();
   defaultConf.set( el::Level::Error, el::ConfigurationType::Enabled, "true" );
   defaultConf.setGlobally( el::ConfigurationType::ToStandardOutput, "false" );
   defaultConf.setGlobally( el::ConfigurationType::ToFile, "true" );

   auto filename = GetFilename( application_name );
   defaultConf.setGlobally( el::ConfigurationType::Filename, filename );

   LOGGER_PTR = el::Loggers::reconfigureLogger( "default", defaultConf );
   el::Loggers::setDefaultConfigurations( defaultConf, true );
}
} // namespace generic::core