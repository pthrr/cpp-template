#include "logging.h"

static auto& logger = logging::getLogger( __FILE__ );

auto main() -> int
{
    logger.info( "Done." );
    return 0;
}
