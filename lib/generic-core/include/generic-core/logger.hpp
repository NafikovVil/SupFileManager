#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#pragma GCC diagnostic ignored "-Wconversion"
#include <easylogging++.h>
#pragma GCC diagnostic pop

// Simple and stupid logger implementation
namespace generic::core
{

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

} // namespace generic::core