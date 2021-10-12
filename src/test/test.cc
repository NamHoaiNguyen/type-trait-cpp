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
    BOOST_TEST(bool(is_union_v<E>) == false);

    BOOST_TEST(bool(is_class_v<C>) == true);
    BOOST_TEST(bool(is_class_v<E>) == false);

    BOOST_TEST(bool(is_pointer_v<int*>) ==  true);
    BOOST_TEST(bool(is_pointer_v<C**>) ==  true);
    BOOST_TEST(bool(is_pointer_v<float&&>) ==  false);

    BOOST_TEST(bool(is_lvalue_reference_v<C>) ==  false);
    BOOST_TEST(bool(is_lvalue_reference_v<C&>) ==  true);
    BOOST_TEST(bool(is_lvalue_reference_v<C&&>) ==  false);

    BOOST_TEST(bool(is_rvalue_reference_v<C>) ==  false);
    BOOST_TEST(bool(is_rvalue_reference_v<C&>) ==  false);
    BOOST_TEST(bool(is_rvalue_reference_v<C&&>) ==  true);

}

BOOST_AUTO_TEST_CASE(test_composite_categories) {
    using namespace composite_categories;

    class C {};
    BOOST_TEST(bool(is_arithmetic_v<C>) == false);
    BOOST_TEST(bool(is_arithmetic_v<int>) == true);
    BOOST_TEST(bool(is_arithmetic_v<int const>) == false); /*true?*/ 
    BOOST_TEST(bool(is_arithmetic_v<float>) == true);
    BOOST_TEST(bool(is_arithmetic_v<float const&>) == false);
    BOOST_TEST(bool(is_arithmetic_v<char>) == true);
    BOOST_TEST(bool(is_arithmetic_v<char&&>) == false);

    BOOST_TEST(bool(is_fundamental_v<C>) == false);
    BOOST_TEST(bool(is_fundamental_v<int>) == true);
    BOOST_TEST(bool(is_fundamental_v<decltype(nullptr)>) == true);
    BOOST_TEST(bool(is_fundamental_v<void>) == true);

    BOOST_TEST(bool(is_scalar_v<C>) == false);
    BOOST_TEST(bool(is_scalar_v<int** const volatile>) == true);

    BOOST_TEST(bool(is_object_v<int>) == true);
    BOOST_TEST(bool(is_object_v<int&>) == false);
    BOOST_TEST(bool(is_object_v<C>) == true);
    BOOST_TEST(bool(is_object_v<C&>) == false);

    BOOST_TEST(bool(is_compound_v<C>) == true);
    BOOST_TEST(bool(is_compound_v<int>) == false);

    BOOST_TEST(bool(is_reference_v<C>) == false);
    BOOST_TEST(bool(is_reference_v<C&>) == true);
    BOOST_TEST(bool(is_reference_v<C&&>) == true);

    BOOST_TEST(bool(is_member_pointer_v<int(C::*)>) == true);
    BOOST_TEST(bool(is_member_pointer_v<int>) == false);
}

BOOST_AUTO_TEST_CASE(test_type_properties) {
    using namespace type_properties;

    TEST_LOG();
}

BOOST_AUTO_TEST_CASE(test_supported_operations_) {
    using namespace supported_operations;

    TEST_LOG();
}

BOOST_AUTO_TEST_CASE(test_property_queries) {
    using namespace property_queries;

    TEST_LOG();
}


BOOST_AUTO_TEST_CASE(test_references) {
    using namespace references;
    using namespace type_relationships;

    TEST_LOG();

    BOOST_TEST(bool(is_same_v<remove_reference_t<int&&>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_reference_t<int&>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_reference_t<int&>, float>) == false);
}

BOOST_AUTO_TEST_CASE(test_pointer) {
    using namespace pointers;
    using namespace type_relationships;

    TEST_LOG();

    BOOST_TEST(bool(is_same_v<remove_pointer_t<int*>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_pointer_t<int* const volatile>, int>) == true);
    BOOST_TEST(bool(is_same_v<remove_pointer_t<int*>, float>) == false);
} 

BOOST_AUTO_TEST_CASE(test_sign_modifiers) {
    using namespace sign_modifiers;

    TEST_LOG();
}

BOOST_AUTO_TEST_CASE(test_arrays) {
    using namespace arrays;

    TEST_LOG();
}

BOOST_AUTO_TEST_CASE(test_miscellaneous_transformation) {
    using namespace miscellaneous_transformation;

    TEST_LOG();
}

BOOST_AUTO_TEST_CASE(test_operations_on_traits) {
    using namespace operations_on_traits;

    TEST_LOG();
}

BOOST_AUTO_TEST_CASE(test_member_relationships) {
    using namespace members_relationships;

    TEST_LOG();
}

BOOST_AUTO_TEST_CASE(test_constant_evaluation_context) {
    using namespace constant_evaluation_context;
    
    TEST_LOG();
}