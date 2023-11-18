#include <iostream>

auto inline print( const char* msg ) -> int
{
    std::cout << msg << std::endl;
    return 0;
}
