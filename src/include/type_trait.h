template<typename T, T v>
struct integral_constant {
    using value_type = T;
    static constexpr T value =  v;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
};

template<bool T>
using bool_constant = integral_constant<bool, T>;

template<bool T>
using true_type =  integral_constant<bool,  true>;

template<bool T>
using false_type = integral_constant<bool, false>;