#include <exception>
#include <fstream>
#include <string>

#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

auto main( int argc, char** argv ) -> int
{
    argparse::ArgumentParser program( "my_program" );
    spdlog::level::level_enum log_level = spdlog::level::info;

    program.add_argument( "--debug" )
        .help( "enable debug mode" )
        .default_value( false )
        .implicit_value( true );

    program.add_argument( "-c", "--config" )
        .help( "Path to the config file" )
        .default_value( std::string( "config.txt" ) );

    try {
        program.parse_args( argc, argv );
    }
    catch( const std::runtime_error& err ) {
        SPDLOG_ERROR( "Error parsing arguments: {}", err.what() );
        return 1;
    }

    if( program.get< bool >( "--debug" ) ) {
        log_level = spdlog::level::debug;
    }

    std::ifstream file( program.get< std::string >( "--config" ) );
    nlohmann::json json_config{};
    std::string app_name{};

    try {
        file >> json_config;
        app_name = json_config["app"]["name"].get< std::string >();
    }
    catch( const nlohmann::json::exception& err ) {
        SPDLOG_ERROR( "Error parsing config: {}", err.what() );
        return 1;
    }

    SPDLOG_INFO( "Starting {} ..", app_name );
    spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] [%s:%#] %v" );
    spdlog::set_level( log_level );
    SPDLOG_INFO( "Done." );
    return 0;
}
