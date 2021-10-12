/*Helper classes*/

template<typename T, T v>
struct integral_constant {
    using value_type = T;
    static constexpr T value =  v;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = integral_constant<bool, true>;

using false_type = integral_constant<bool, false>;

/*Const-volatility specifiers*/
namespace remove_const_volatile {
    template<typename T>
    struct remove_const {
        using type = T;
    };

    template<typename T>
    struct remove_const<T const> {
        using type = T;
    };

    template<typename T>
    using remove_const_t = typename remove_const<T>::type;

    template<typename T>
    struct remove_volatile {
        using type = T;
    };

    template<typename T>
    struct remove_volatile<T volatile> {
        using type = T;
    };

    template<typename T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    template<typename T>
    struct remove_cv {
        using type = T;
    };

    template<typename T>
    struct remove_cv<T const> : public remove_const<T> {
        using type = T;
    };

    template<typename T>
    struct remove_cv<T volatile> : public remove_volatile<T> {
        using type = T;
    };

    template<typename T>
    struct remove_cv<T const volatile> {
        using type = T;
    };

    template<typename T>
    using remove_cv_t = typename remove_cv<T>::type;
};

/*Type relationships*/
namespace type_relationships {
    template<typename T, typename U>
    struct is_same : public false_type { };

    template<typename T>
    struct is_same<T, T> : public true_type { };

    template<typename T, typename U>
    inline constexpr bool is_same_v = is_same<T, U>::value;
}

/*Prmary type categories*/
namespace type_categories{
    using namespace remove_const_volatile;
    using namespace type_relationships;

    template<typename T>
    struct is_void_helper : public false_type { };

    template<>
    struct is_void_helper<void> : public true_type { };

    template<typename T>
    struct is_void : public is_void_helper<remove_cv_t<T>> { };

/* Other implementation of is_void
    template<typename T>
    struct is_void : public is_same<void, remove_cv_t<T>> { };
*/
    template<typename T>

    inline constexpr bool is_void_v = is_void<T>::value;

/* Another implementation of is_null_pointer
    template<typename T>
    struct is_null_pointer_helper : public false_type { };

    template<>
    struct is_null_pointer_helper<decltype(nullptr)> : public true_type { };

    template<typename T>
    struct is_null_pointer : public is_null_pointer_helper<remove_cv_t<T>> { };
*/

    template<typename T>
    struct is_null_pointer : public is_same<decltype(nullptr), remove_cv_t<T>> { };
    
    template<typename T>
    inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

    template<typename T>
    struct is_integral : public false_type { };

    template<>
    struct is_integral<bool> : public true_type { };

    template<>
    struct is_integral<char> : public true_type { };

/* Since c++20
    template<>
    struct is_integral<char8_t> : true_type { };
*/
    template<>
    struct is_integral<char16_t> : public true_type { };

    template<>
    struct is_integral<char32_t> : public true_type { };

    template<>
    struct is_integral<wchar_t> : public true_type { };

    template<>
    struct is_integral<short> : public true_type { };

    template<>
    struct is_integral<int> : public true_type { };

    template<>
    struct is_integral<long> : public true_type { };

    template<>
    struct is_integral<long long> : public true_type { };

    template<typename T>
    inline constexpr bool is_integral_v = is_integral<T>::value;

    template<typename T>
    struct is_floating_point : public false_type { };

    template<>
    struct is_floating_point<float> : public true_type { };

    template<>
    struct is_floating_point<double> : public true_type { };

    template<>
    struct is_floating_point<long double> : public true_type { };

    template<typename T>
    inline constexpr bool is_floating_point_v = is_floating_point<T>::value;

    template<typename T>
    struct is_array : public false_type { };

    template<typename T>
    struct is_array<T[]> : public true_type { };

    template<typename T, std::size_t N>
    struct is_array<T[N]> : public true_type { };

    template<typename T>
    inline constexpr bool is_array_v = is_array<T>::value;

    enum E{};

    //Note : __is_enum and __is_union is compiler feature
    template<typename T>
    struct is_enum : public integral_constant<bool, __is_enum(T)> { };

    template<typename T>
    inline constexpr bool is_enum_v = is_enum<T>::value;

    template<typename T>
    struct is_union : public integral_constant<bool, __is_union(T)> { };

    template<typename T>
    inline constexpr bool is_union_v = is_union<T>::value;

    template<typename T>
    struct is_class : public integral_constant<bool, __is_class(T)> { };

    template<typename T>
    inline constexpr bool is_class_v = is_class<T>::value;

    // template<typename T>
    // struct is_function : public integral_constant<bool, __is_class(T)> {

    // };

    // template<typename T>
    // inline constexpr bool is_function_v = is_function<T>::value;

    template<typename T>
    struct is_pointer_helper : public false_type { };

    template<typename T>
    struct is_pointer_helper<T*> : public true_type { };

    template<typename T>
    struct is_pointer : public is_pointer_helper<remove_cv_t<T>> { };
    
    template<typename T>
    inline constexpr bool is_pointer_v = is_pointer<T>::value;

    template<typename T>
    struct is_lvalue_reference : public false_type { };

    template<typename T>
    struct is_lvalue_reference<T&> : public true_type { };

    template<typename T>
    inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

    template<typename T>
    struct is_rvalue_reference : public false_type { };

    template<typename T>
    struct is_rvalue_reference<T&&> : public true_type { };

    template<typename T>
    inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

    // is_member_object_pointer
    // is_member_function_pointers
}

/*Composite type categories*/
namespace composite_categories {
    using namespace type_categories;

    template<typename T>
    struct is_arithmetic : public integral_constant<bool, 
                                                    is_integral_v<T> ||
                                                    is_floating_point_v<T>> { };
    
    template<typename T>
    inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

    template<typename T>
    struct is_fundamental : public integral_constant<bool,
                                                     is_arithmetic_v<T> ||
                                                     is_void_v<T> ||
                                                     is_null_pointer_v<T>> { };

    template<typename T>
    inline constexpr bool is_fundamental_v = is_fundamental<T>::value;

    template<typename T>
    struct is_member_pointer_helper : public false_type { };

    template<typename T, typename U>
    struct is_member_pointer_helper<T U::*> : public true_type { };

    template<typename T>
    struct is_member_pointer : public is_member_pointer_helper<remove_cv_t<T>> { };

    template<typename T>
    inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

    template< class T >
    struct is_scalar : public std::integral_constant<bool,
                        is_arithmetic_v<T>     ||
                        is_enum_v<T>           ||
                        is_pointer_v<T>        ||
                        is_member_pointer_v<T> ||
                        is_null_pointer_v<T>> { };

    template<typename T>
    inline constexpr bool is_scalar_v = is_scalar<T>::value;

    template< class T>
    struct is_object : public integral_constant<bool,
                        is_scalar_v<T> ||
                        is_array_v<T>  ||
                        is_union_v<T>  ||
                        is_class_v<T>> { };

    template<typename T>
    inline constexpr bool is_object_v = is_object<T>::value;

    template<typename T>
    struct is_compound : public integral_constant<bool, 
                                                  !is_fundamental_v<T>>
                                                  { };

    template<typename T>
    inline constexpr bool is_compound_v = is_compound<T>::value;     

    template<typename T>
    struct is_reference : public false_type { };
    
    template<typename T>
    struct is_reference<T&> : public true_type { };

    template<typename T>
    struct is_reference<T&&> : public true_type { };

    template<typename T>
    inline constexpr bool is_reference_v = is_reference<T>::value;
}

namespace type_properties {

}

namespace supported_operations {

}

namespace property_queries {

}

/*Reference*/
namespace references {
    template<typename T>
    struct remove_reference {
        using type = T;
    };

    template<typename T>
    struct remove_reference<T&> {
        using type = T;
    };

    template<typename T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    template<typename T>
    struct add_lvalue_referece {

    };

    // template<typename T>
}

/*Pointer*/
namespace pointers {
    template<typename T>
    struct remove_pointer {

    };

    template<typename T>
    struct remove_pointer<T*> {
        using type = T;
    };

    template<typename T>
    struct remove_pointer<T* const> {
        using type = T;
    };

    template<typename T>
    struct remove_pointer<T* volatile> {
        using type = T;
    };

    template<typename T>
    struct remove_pointer<T* const volatile> {
        using type = T;
    };

    // template<typename T>
    // using remove_pointer_t = typename remove_pointer<T>::type;
    template<typename T>
    using remove_pointer_t = typename remove_pointer<T>::type;
}

namespace sign_modifiers {

}

namespace arrays {

}

/*Miscellaneous transformations*/
namespace miscellaneous_transformation {
    template<bool B, typename T = void>
    struct enable_if {
        
    };

    template<typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template<bool B, class T = void>
    using enable_if_t = typename enable_if<B, T>::type;
}

namespace operations_on_traits {

}

namespace members_relationships {

}

namespace constant_evaluation_context {

}

// template<typename T>
// inline constexpr bool remove_pointer_t = typename pointer::remove_pointer<T>::type;