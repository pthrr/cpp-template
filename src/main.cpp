#include <iostream>

auto print( const char* msg ) -> int
{
    std::cout << msg << std::endl;
    return 0;
}

auto main() -> int
{
    return print( "Hello World!" );
}
