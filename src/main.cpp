#include <fstream>
#include <iostream>

#include <spdlog/spdlog.h>

#include "config.h"

auto main() -> int
{
    XMLConfigLoader loader( "config.xml", "schema.xsd" );
    std::string app_name{};

    if( loader.loadAndValidate() ) {
        app_name = loader.getAppName( "/config/appName" );
    }
    else {
        SPDLOG_ERROR( "Failed to load or validate XML." );
        return -1;
    }

    SPDLOG_INFO( "Starting {} ..", app_name );
    spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] [%s:%#] %v" );
    spdlog::set_level( spdlog::level::debug );
    SPDLOG_INFO( "Done." );
    return 0;
}
