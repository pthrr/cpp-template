#include <gtest/gtest.h>

#include "../src/main.cpp"

TEST( main, print )
{
    auto rv = print( "My message" );
    ASSERT_TRUE( rv == 0 );
}
