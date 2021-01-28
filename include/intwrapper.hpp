/*
    Copyright © 2021 Luiz Fernando F. G. Valle
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file intwrapper.hpp
 * @author Luiz Fernando F. G. Valle
 * @brief Provides a wrapper that provides overflow protection for integral
 *          types.
 * @version 1.0
 * @date 2021-01-28
 *
 * @copyright Copyright (c) 2021
 */





#ifndef OVERFLOWWRAPPER_INCLUDE_INTWRAPPER_HPP
#define OVERFLOWWRAPPER_INCLUDE_INTWRAPPER_HPP

#include <stdexcept>

#include "../src/overflow_checks.hpp"





namespace overflow
{

// -------------------------------------------------------------------------- >>
//                                 IntWrapper                                 >>
// -------------------------------------------------------------------------- >>

/**
 * @brief Wraps around an integral type and provides overflow protection.
 *
 * @tparam T Wrapped integral type
 */
template <std::integral T = int>
class IntWrapper
{





// Public type aliases ------------------------------------------------------ >>

public:
    /**
     * @brief Alias to this class.
     */
    using self_type = IntWrapper<T>;

    /**
     * @brief Stored type.
     */
    using value_type = T;





// RAII --------------------------------------------------------------------- >>

    /**
     * @brief Constructs a new instance and initializes value as zero.
     */
    constexpr IntWrapper() = default;

    /**
     * @brief Initializes a new instance with the desired value.
     *
     * @tparam ArgT Argument's type
     * @param val Integral value
     */
    template <std::integral ArgT>
    constexpr IntWrapper(const ArgT &val)
    {
        if (checks::Assign<value_type, ArgT>(val))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::IntWrapper<ArgT>(const ArgT&)");

        value = val;
    }





// Assignment operator overloads -------------------------------------------- >>

    /**
     * @brief Assigns an integer to the object.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator=(const RhsT &rhs)
    {
        if (checks::Assign<value_type, RhsT>(rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator=<RhsT>(const RhsT&)");

        value = rhs;

        return *this;
    }

    template <std::integral RhsWrappedT>
    constexpr self_type &operator=(const IntWrapper<RhsWrappedT> &rhs)
    {
        return operator=(rhs.Get());
    }

    /**
     * @brief Adds an integer to the object's value.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator+=(const RhsT &rhs)
    {
        if (checks::Sum(value, rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator+=(const value_type&)");

        value += rhs;

        return *this;
    }

    /**
     * @brief Subtracts an integer from the object's value.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator-=(const RhsT &rhs)
    {
        if (checks::Sub(value, rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator-=(const value_type&)");

        value -= rhs;

        return *this;
    }

    /**
     * @brief Multiplies the object's value by an integer.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator*=(const RhsT &rhs)
    {
        if (checks::Mul(value, rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator*=(const value_type&)");

        value *= rhs;

        return *this;
    }

    /**
     * @brief Divides the object's value by an integer.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator/=(const RhsT &rhs)
    {
        if (checks::Div(value, rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator/=(const value_type&)");

        value /= rhs;

        return *this;
    }

    /**
     * @brief Bitwise AND of the object's value and an integer.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator&=(const RhsT &rhs)
    {
        value &= rhs;

        return *this;
    }

    /**
     * @brief Bitwise XOR of the object's value and an integer.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator^=(const RhsT &rhs)
    {
        value ^= rhs;

        return *this;
    }

    /**
     * @brief Bitwise OR of the object's value and an integer.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator|=(const RhsT &rhs)
    {
        value |= rhs;

        return *this;
    }

    /**
     * @brief Bitwise left shift of the object's value and an integer.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator<<=(const RhsT &rhs)
    {
        value <<= rhs;

        return *this;
    }

    /**
     * @brief Bitwise right shift of the object's value and an integer.
     *
     * @tparam RhsT Right-hand argument's integral type
     * @param rhs Integral operand
     * @return Reference to self
     */
    template <std::integral RhsT>
    constexpr self_type &operator>>=(const RhsT &rhs)
    {
        value >>= rhs;

        return *this;
    }





// Unary operators ---------------------------------------------------------- >>

    /**
     * @brief Bitwise NOT of the object's value.
     *
     * @return Reference to self
     */
    constexpr self_type operator~() const { return ~value; }

    /**
     * @brief Gets read-only address of the stored value.
     *
     * @return Pointer to the const stored value
     */
    constexpr const T *operator&() const { return &value; }

    // Not sure if there is any reason to use constexpr here

    /**
     * @brief Gets the address of the stored value.
     *
     * @return Pointer to the stored value
     */
    constexpr T *operator&() { return &value; }





// Conversion operators ----------------------------------------------------- >>

    /**
     * @brief Converts the wrapper to the wrapped type.
     *
     * @return Stored value
     */
    constexpr operator T() const { return value; }





// Getters and setters ------------------------------------------------------ >>

    /**
     * @brief Returns a const reference to the wrapper's stored value.
     *
     * @return Const reference to the stored value
     */
    constexpr const T &Get() const { return value; }

    /**
     * @brief Returns a reference to the wrapper's stored value.
     *
     * @return Reference to the stored value
     */
    constexpr T &Get() { return value; }





// Private member variables ------------------------------------------------- >>

private:

    T value{};
};










// Other operators ---------------------------------------------------------- >>

/**
 * @brief Adds a wrapped integer to the the object's value.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integer wrapper
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator+=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs += rhs.Get();
}

/**
 * @brief Subtracts a wrapped integer from the object's value.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integer wrapper
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator-=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs -= rhs.Get();
}

/**
 * @brief Multiplies the object's value by a wrapped integer.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integer wrapper
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator*=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs *= rhs.Get();
}

/**
 * @brief Divides the object's value by a wrapped integer.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integer wrapper
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator/=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs /= rhs.Get();
}

/**
 * @brief Bitwise AND of the object's value and a wrapped integer.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integral operand
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator&=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs &= rhs.Get();
}

/**
 * @brief Bitwise XOR of the object's value and a wrapped integer.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integral operand
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator^=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs ^= rhs.Get();
}

/**
 * @brief Bitwise OR of the object's value and a wrapped integer.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integral operand
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator|=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs |= rhs.Get();
}

/**
 * @brief Bitwise left shift of the object's value and a wrapped integer.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integral operand
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator<<=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs <<= rhs.Get();
}

/**
 * @brief Bitwise right shift of the object's value and a wrapped integer.
 *
 * @tparam RhsWrappedT Wrapped integer type
 * @param rhs Integral operand
 * @return Reference to self
 */
template <std::integral LhsWrappedT, std::integral RhsWrappedT>
constexpr auto &operator>>=(IntWrapper<LhsWrappedT> &lhs,
                    const IntWrapper<RhsWrappedT> &rhs)
{
    return lhs >>= rhs.Get();
}

/**
 * @brief Increments the wrapped value (prefix).
 *
 * @tparam T Wrapped type
 * @param operand Integer wrapper
 * @return Reference to the operand
 */
template <typename T>
constexpr IntWrapper<T> &operator++(IntWrapper<T> &operand) { return operand += 1; }

/**
 * @brief Increments the wrapped value (postfix).
 *
 * @tparam T Wrapped type
 * @param operand Integer wrapper
 * @return Copy of the operand before incrementing
 */
template <typename T>
constexpr IntWrapper<T> operator++(IntWrapper<T> &operand, int)
{
    IntWrapper<T> retval{operand};
    ++operand;
    return retval;
}

/**
 * @brief Decrements the wrapped value (prefix).
 *
 * @tparam T Wrapped type
 * @param operand Integer wrapper
 * @return Reference to the operand
 */
template <typename T>
constexpr IntWrapper<T> &operator--(IntWrapper<T> &operand) { return operand -= 1; }

/**
 * @brief Decrements the wrapped value (postfix).
 *
 * @tparam T Wrapped type
 * @param operand Integer wrapper
 * @return Copy of the operand before decrementing
 */
template <typename T>
constexpr IntWrapper<T> operator--(IntWrapper<T> &operand, int)
{
    IntWrapper<T> retval{operand};
    --operand;
    return retval;
}

} // namespace overflow

#endif // #ifndef OVERFLOWWRAPPER_INCLUDE_INTWRAPPER_HPP