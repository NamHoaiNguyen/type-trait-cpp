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
    struct is_same : public false_type {

    };

    template<typename T>
    struct is_same<T, T> : public true_type {

    };

    template<typename T, typename U>
    inline constexpr bool is_same_v = is_same<T, U>::value;
}

/*Prmary type categories*/
namespace type_categories{
    using namespace remove_const_volatile;
    using namespace type_relationships;

    template<typename T>
    struct is_void_helper : public false_type {

    };

    template<>
    struct is_void_helper<void> : public true_type {

    };

    template<typename T>
    struct is_void : public is_void_helper<remove_cv_t<T>> {

    };

/* Other implementation of is_void
    template<typename T>
    struct is_void : public is_same<void, remove_cv_t<T>> {

    };
*/
    template<typename T>

    inline constexpr bool is_void_v = is_void<T>::value;

/* Another implementation of is_null_pointer
    template<typename T>
    struct is_null_pointer_helper : public false_type {

    };

    template<>
    struct is_null_pointer_helper<decltype(nullptr)> : public true_type {

    };

    template<typename T>
    struct is_null_pointer : public is_null_pointer_helper<remove_cv_t<T>> {

    };
*/

    template<typename T>
    struct is_null_pointer : is_same<decltype(nullptr), remove_cv_t<T>> {

    };
    
    template<typename T>
    inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

    template<typename T>
    struct is_integral : false_type {

    };

    template<>
    struct is_integral<bool> : true_type {

    };

    template<>
    struct is_integral<char> : true_type {

    };

    template<typename T>
    inline constexpr bool is_integral_v = is_integral<T>::value;
}

/*Miscellaneous transformations*/
namespace transformation {
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

// /*Type relationships*/
// namespace type_relationships {
//     template<typename T, typename U>
//     struct is_same : public false_type {

//     };

//     template<typename T>
//     struct is_same<T, T> : public true_type {

//     };

//     template<typename T, typename U>
//     inline constexpr bool is_same_v = is_same<T, U>::value;
// }


/*const-volatility specifiers*/


/*Reference*/
namespace reference {
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
namespace pointer {
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
    using remove_pointer_t = typename pointer::remove_pointer<T>::type;
}

// template<typename T>
// inline constexpr bool remove_pointer_t = typename pointer::remove_pointer<T>::type;