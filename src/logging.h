#pragma once

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <string>

static auto extractFileName( const std::string& filePath ) -> std::string
{
    size_t pos = filePath.find_last_of( "/\\" );

    if( pos != std::string::npos ) {
        return filePath.substr( pos + 1 );
    }

    return filePath;
}

namespace logging {

spdlog::logger& getLogger( const std::string& name )
{
    auto logger = spdlog::get( extractFileName( name ) );

    if( !logger ) {
        logger = spdlog::stdout_color_mt( extractFileName( name ) );
    }

    return *logger;
}

} // namespace logging
