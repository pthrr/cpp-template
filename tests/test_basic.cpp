#include <gtest/gtest.h>

#include "../src/print.hpp"

TEST( basic, print )
{
    auto rval = print( "My message" );
    ASSERT_TRUE( rval == 0 );
}
