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
 * @date 2021-01-26
 *
 * @copyright Copyright (c) 2021
 */





#ifndef OVERFLOWWRAPPER_INCLUDE_INTWRAPPER_HPP
#define OVERFLOWWRAPPER_INCLUDE_INTWRAPPER_HPP

#include <stdexcept>

#include "../src/overflow_checks.hpp"





namespace overflow
{

/* -------------------------------------------------------------------------- */
/*                                 IntWrapper                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Wraps around an integral type and provides overflow protection.
 *
 * @tparam T Wrapped integral type
 */
template <std::integral T = int>
class IntWrapper
{





/* --------------------------- Public type aliases -------------------------- */

public:
    /**
     * @brief Alias to this class.
     */
    using self_type = IntWrapper<T>;

    /**
     * @brief Stored type.
     */
    using value_type = T;





/* ---------------------------------- RAII ---------------------------------- */

    /**
     * @brief Constructs a new instance and initializes value as zero.
     */
    constexpr IntWrapper() = default;

    /**
     * @brief Initializes a new instance with the desired value.
     *
     * @param value Desired value
     */
    constexpr IntWrapper(const value_type &value) : value{value} {}





/* --------------------------- Operator overloads --------------------------- */

    /**
     * @brief Assigns an integer to the object.
     *
     * @param rhs Source integer
     * @return Reference to self
     */
    self_type &operator=(const value_type &rhs)
    {
        value = rhs;

        return *this;
    }

    /**
     * @brief Adds an integer to the object's value.
     *
     * @param rhs Integral operand
     * @return Reference to self
     */
    self_type &operator+=(const value_type &rhs)
    {
        if (checks::Sum(value, rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator+=(const value_type &rhs)");

        value += rhs;

        return *this;
    }

    /**
     * @brief Subtracts an integer from the object's value.
     *
     * @param rhs Integral operand
     * @return Reference to self
     */
    self_type &operator-=(const value_type &rhs)
    {
        if (checks::Sub(value, rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator-=(const value_type &rhs)");

        value -= rhs;

        return *this;
    }

    /**
     * @brief Multiplies the object's value by an integer.
     *
     * @param rhs Integral operand
     * @return Reference to self
     */
    self_type &operator*=(const value_type &rhs)
    {
        if (checks::Mul(value, rhs))
            throw std::overflow_error("Integer overflow in IntWrapper<T>::operator*=(const value_type &rhs)");

        value *= rhs;

        return *this;
    }

    //
    // TODO: operator/=
    //

    constexpr operator T() { return value; }





/* --------------------------- Getters and setters -------------------------- */

    /**
     * @brief Returns the wrapper's stored value.
     *
     * @return Stored value
     */
    constexpr T Get() const { return value; }





/* ------------------------ Private member variables ------------------------ */

private:
    T value{};
};





/* ----------------------------- Other operators ---------------------------- */

/**
 * @brief Computes the sum of the wrapped value and another integer.
 *
 * @tparam T Integral type of the right-hand operand
 * @param lhs Integer wrapper
 * @param rhs Right-hand integer operand
 * @return Value of the computation
 */
template <typename T>
constexpr T operator+(IntWrapper<T> lhs, const T &rhs) { return T(lhs += rhs); }

/**
 * @brief Computes the subtraction of the right-hand integer from the wrapped
 *          value.
 *
 * @tparam T Integral type of the right-hand operand
 * @param lhs Integer wrapper
 * @param rhs Right-hand integer operand
 * @return Value of the computation
 */
template <typename T>
constexpr T operator-(IntWrapper<T> lhs, const T &rhs) { return T(lhs -= rhs); }

/**
 * @brief Computes the product of the wrapped value and another integer.
 *
 * @tparam T Integral type of the right-hand operand
 * @param lhs Integer wrapper
 * @param rhs Right-hand integer operand
 * @return Value of the computation
 */
template <typename T>
constexpr T operator*(IntWrapper<T> lhs, const T &rhs) { return T(lhs *= rhs); }

//
// TODO: operator/
//

/**
 * @brief Increments the wrapped value (prefix).
 *
 * @tparam T Wrapped type
 * @param operand Integer wrapper
 * @return Reference to the operand
 */
template <typename T>
IntWrapper<T> &operator++(IntWrapper<T> &operand) { return operand += 1; }

/**
 * @brief Increments the wrapped value (postfix).
 *
 * @tparam T Wrapped type
 * @param operand Integer wrapper
 * @return Copy of the operand before incrementing
 */
template <typename T>
IntWrapper<T> operator++(IntWrapper<T> &operand, int)
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
IntWrapper<T> &operator--(IntWrapper<T> &operand) { return operand -= 1; }

/**
 * @brief Decrements the wrapped value (postfix).
 *
 * @tparam T Wrapped type
 * @param operand Integer wrapper
 * @return Copy of the operand before decrementing
 */
template <typename T>
IntWrapper<T> operator--(IntWrapper<T> &operand, int)
{
    IntWrapper<T> retval{operand};
    --operand;
    return retval;
}

} // namespace overflow

#endif // #ifndef OVERFLOWWRAPPER_INCLUDE_INTWRAPPER_HPP