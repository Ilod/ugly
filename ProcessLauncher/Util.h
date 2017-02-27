#pragma once

#include <type_traits>

namespace ugly
{
    template<typename T> constexpr const bool is_enum_flag = false;

    template<typename T = typename std::enable_if<is_enum_flag<T>, T>::type>
    class auto_bool
    {
    private:
        T val_;
    public:
        constexpr auto_bool(T val) : val_(val) {}
        constexpr operator T() const { return val_; }
        constexpr explicit operator bool() const
        {
            return static_cast<std::underlying_type_t<T>>(val_) != 0;
        }
    };

    template <typename T>
    std::enable_if_t<is_enum_flag<T>, auto_bool<T>> operator&(T lhs, T rhs)
    {
        return static_cast<T>(
            static_cast<typename std::underlying_type<T>::type>(lhs) &
            static_cast<typename std::underlying_type<T>::type>(rhs));
    }

    template <typename T>
    std::enable_if_t<is_enum_flag<T>, T> operator|(T lhs, T rhs)
    {
        return static_cast<T>(
            static_cast<typename std::underlying_type<T>::type>(lhs) |
            static_cast<typename std::underlying_type<T>::type>(rhs));
    }
}