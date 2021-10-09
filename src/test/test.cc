#define BOOST_TEST_MODULE stl_algorithms_test

#include <boost/test/included/unit_test.hpp>
#include "../include/type_trait.h"

BOOST_AUTO_TEST_CASE (test_integral_constant) { 
    typedef integral_constant<int, 2> two_t;
    typedef integral_constant<int, 4> four_t;
    static_assert(two_t::value*2 == four_t::value,
       "2*2 != 4"
    );
}