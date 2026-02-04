#pragma once

#include <print>
#include <source_location>

#include <common/types.hpp>

#ifdef NDEBUG
#define DEBUG_ASSERT( condition ) ( (void)0 )
#else
#define DEBUG_ASSERT( condition ) assert( condition )
#endif

#ifdef NDEBUG
#define DBG( x ) ( x )
#else
#define DBG( x ) oxidize::dbg_impl( ( x ), #x, std::source_location::current() )
#endif

namespace oxidize {

using namespace cmn::types;

template< typename T >
auto dbg_impl( T&& value, str expr, std::source_location const location ) -> T
{
    std::print( "{} = {} ({}:{}:{}:{})\n",
        expr,
        value,
        location.file_name(),
        location.function_name(),
        location.line(),
        location.column() );
    return std::forward< T >( value );
}

} // namespace oxidize
