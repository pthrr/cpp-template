#pragma once

#include <format>

#include "types.hh"

// TODO: use constexpr
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

namespace my_project {

static constexpr inline version_t VERSION{ VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH };

#ifdef NDEBUG
constexpr bool is_debug = false;
#else
constexpr bool is_debug = true;
#endif

static constexpr inline const char* BUILD_VERSION = "<COMMIT_SHA>";
static constexpr inline const char* BUILD_TYPE = is_debug ? "DEBUG" : "RELEASE";

auto getVersionInfo() -> std::string
{
    return std::format( "{}.{}.{}", VERSION.major, VERSION.minor, VERSION.patch );
}

auto getBuildInfo() -> std::string
{
    std::string build_type{ BUILD_TYPE };
    std::string build_version{ BUILD_VERSION };

    if( build_version.compare( "<COMMIT_SHA>" ) == 0 || build_version.empty() ) {
        return build_type;
    }

    return std::format( "{}-{}", build_version, build_type );
}

} // namespace my_project
