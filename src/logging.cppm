export module logging;

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <string>

export namespace logging {

auto getLogger( const std::string& name ) -> spdlog::logger&;
auto getFileLogger( const std::string& filePath ) -> spdlog::logger&;

} // namespace logging
