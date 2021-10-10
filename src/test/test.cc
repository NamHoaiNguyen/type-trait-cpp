#define BOOST_TEST_MODULE type_trait_test

#include <boost/test/included/unit_test.hpp>
#include "type_trait.h"
#include "utils.h"

BOOST_AUTO_TEST_CASE (test_integral_constant) { 
    TEST_LOG();

    typedef integral_constant<int, 2> two_t;
    typedef integral_constant<int, 4> four_t;
    static_assert(two_t::value*2 == four_t::value,
       "2*2 != 4"
    );
}

BOOST_AUTO_TEST_CASE(test_cv_specfier) {
    using namespace remove_const_volatile;
    using namespace type_relationships;

    TEST_LOG();

    BOOST_TEST(bool(is_same_v<remove_const_t<int const>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_const_t<float const>, double>) == false);
    BOOST_TEST(bool(is_same_v<remove_volatile_t<int volatile>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_volatile_t<int volatile>, float>) == false);
    BOOST_TEST(bool(is_same_v<remove_cv_t<int* const >, int*>) == true);
    BOOST_TEST(bool(is_same_v<remove_cv_t<float* volatile>, float*>) == true);
    BOOST_TEST(bool(is_same_v<remove_cv_t<double* const volatile>, double*>) == true);
}

BOOST_AUTO_TEST_CASE(test_type_relationship) {
    using namespace type_relationships;
    using namespace type_categories;
    
    TEST_LOG();
        
    BOOST_TEST(bool(is_same_v<int, int>) == true);
    BOOST_TEST(bool(is_same_v<int, float>) == false);
    // BOOST_TEST(bool(is_void_v<void const volatile>) == true);
}

BOOST_AUTO_TEST_CASE(test_type_categories) {
    using namespace type_categories;
    using namespace type_relationships;

    TEST_LOG();

    BOOST_TEST(bool(is_null_pointer<decltype(nullptr)>::value) == true);
    BOOST_TEST(bool(is_null_pointer<int*>::value) == false);

    class A {};
    enum E {};
    BOOST_TEST(bool(is_integral_v<bool>) == true);
    BOOST_TEST(bool(is_integral_v<char>) == true);
    BOOST_TEST(bool(is_integral_v<char16_t>) == true);
    BOOST_TEST(bool(is_integral_v<char32_t>) == true);
    BOOST_TEST(bool(is_integral_v<wchar_t>) == true);
    BOOST_TEST(bool(is_integral_v<short>) == true);
    BOOST_TEST(bool(is_integral_v<int>) == true);
    BOOST_TEST(bool(is_integral_v<long>) == true);
    BOOST_TEST(bool(is_integral_v<long long>) == true);
    BOOST_TEST(bool(is_integral_v<A>) == false);
    BOOST_TEST(bool(is_integral_v<E>) == false);
    BOOST_TEST(bool(is_integral_v<float>) == false);


    BOOST_TEST(bool(is_floating_point_v<float>) == true);
    BOOST_TEST(bool(is_floating_point_v<double>) == true);
    BOOST_TEST(bool(is_floating_point_v<long double>) == true);
    BOOST_TEST(bool(is_floating_point_v<int*>) == false);

    class C{};
    BOOST_TEST(bool(is_array_v<int* const volatile>) == false);
    BOOST_TEST(bool(is_array_v<int[]>) == true);
    BOOST_TEST(bool(is_array_v<float[10]>) == true);
    BOOST_TEST(bool(is_array_v<C>) == false);
    BOOST_TEST(bool(is_array_v<C[10]>) == true);
    BOOST_TEST(bool(is_array_v<C[]>) == true);

    union U{};
    BOOST_TEST(bool(is_enum_v<E>) == true);
    BOOST_TEST(bool(is_union_v<U>) == true);
}

BOOST_AUTO_TEST_CASE(test_reference) {
    using namespace reference;
    using namespace type_relationships;

    TEST_LOG();

    BOOST_TEST(bool(is_same_v<remove_reference_t<int&&>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_reference_t<int&>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_reference_t<int&>, float>) == false);
}

BOOST_AUTO_TEST_CASE(test_pointer) {
    using namespace pointer;
    using namespace type_relationships;

    TEST_LOG();

    BOOST_TEST(bool(is_same_v<remove_pointer_t<int*>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_pointer_t<int* const volatile>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_pointer_t<int*>, float>) == false);
} 