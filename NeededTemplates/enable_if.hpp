#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

#include <iostream>

namespace ft
{
    template <class T>
    struct is_integral
    {
        typedef bool value_type;
        const static value_type value = false;
    };

    template <>
    struct is_integral<bool>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<char>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<char16_t>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<char32_t>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<wchar_t>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<signed char>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<short int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<long int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<long long int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<unsigned char>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<unsigned short int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<unsigned int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<unsigned long int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };
    template <>
    struct is_integral<unsigned long long int>
    {
        typedef bool value_type;
        const static value_type value = true;
    };

    template <bool cond, class T = void>
    struct enable_if
    {
    };

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };
}

#endif