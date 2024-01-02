#include <spdlog/spdlog.h>

auto main() -> int
{
    spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] [%s:%#] %v" );
    spdlog::set_level( spdlog::level::debug );
    SPDLOG_INFO( "Done." );
    return 0;
}
