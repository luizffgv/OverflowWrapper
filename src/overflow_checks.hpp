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
 * @file overflow_checks.hpp
 * @author Luiz Fernando F. G. Valle
 * @brief Provides integer overflow-checking functions.
 * @version 1.0
 * @date 2021-01-26
 *
 * @copyright Copyright (c) 2021
 */





#ifndef OVERFLOWWRAPPER_SRC_OVERFLOW_CHECKS_HPP
#define OVERFLOWWRAPPER_SRC_OVERFLOW_CHECKS_HPP

#include <concepts>
#include <limits>





namespace overflow::checks
{

/* -------------------------------------------------------------------------- */
/*                         Overflow checking functions                        */
/* -------------------------------------------------------------------------- */

/**
 * @brief Checks if a subtraction causes integer overflow.
 *        Should work in the vast majority of implementations.
 *
 * @tparam LhsT Left-hand operand's integral type
 * @tparam RhsT Right-hand operand's integral type
 * @param lhs Left-hand operand
 * @param rhs Right-hand operand
 * @return true Causes integer overflow
 * @return false Does not cause integer overflow
 */
template <std::integral LhsT, std::integral RhsT>
[[nodiscard]] constexpr bool Sub(const LhsT &lhs, const RhsT &rhs)
{
    return (rhs < 0 && lhs > std::numeric_limits<LhsT>::max() + rhs
            || rhs > 0 && lhs < std::numeric_limits<LhsT>::min() + rhs);
}





/**
 * @brief Checks if an addition causes integer overflow.
 *        Should work in the vast majority of implementations.
 *
 * @tparam LhsT Left-hand operand's integral type
 * @tparam RhsT Right-hand operand's integral type
 * @param lhs Left-hand operand
 * @param rhs Right-hand operand
 * @return true Causes integer overflow
 * @return false Does not cause integer overflow
 */
template <std::integral LhsT, std::integral RhsT>
[[nodiscard]] constexpr bool Sum(const LhsT &lhs, const RhsT &rhs)
{
    if (rhs < 0)
    {
        if (rhs == std::numeric_limits<RhsT>::min())
            // Possible overflow when sign is flipped
            return true;
        return Sub(lhs, -rhs);
    }
    if (lhs >= 0)
        return std::numeric_limits<LhsT>::max() - lhs < rhs;
    return std::numeric_limits<LhsT>::max() - rhs < lhs;
}





/**
 * @brief Checks if a multiplication causes integer overflow.
 *        Should work in the vast majority of implementations.
 *
 * @tparam LhsT Left-hand operand's integral type
 * @tparam RhsT Right-hand operand's integral type
 * @param lhs Left-hand operand
 * @param rhs Right-hand operand
 * @return true Causes integer overflow
 * @return false Does not cause integer overflow
 */
template <std::integral LhsT, std::integral RhsT>
[[nodiscard]] constexpr bool Mul(const LhsT &lhs, const RhsT &rhs)
{
    // TODO: Use a better algorithm

    if (lhs == 0 || rhs == 0)
        return false;

    if (lhs < 0)
    {
        if (rhs < 0)
        {
            if (lhs == std::numeric_limits<LhsT>::min()
                || rhs == std::numeric_limits<LhsT>::min())
            {
                return true;
            }
            return Mul(-lhs, -rhs);
        }
        else
            return std::numeric_limits<LhsT>::min() / lhs < rhs;
    }
    if (rhs < 0)
        return std::numeric_limits<LhsT>::min() / rhs < lhs;
    return std::numeric_limits<LhsT>::max() / lhs < rhs;
}





/**
 * @brief Checks if a division causes integer overflow.
 *        Should work in the vast majority of implementations.
 *
 * @tparam LhsT Left-hand operand's integral type
 * @tparam RhsT Right-hand operand's integral type
 * @param lhs Left-hand operand
 * @param rhs Right-hand operand
 * @return true Causes integer overflow
 * @return false Does not cause integer overflow
 */
template <std::integral LhsT, std::integral RhsT>
[[nodiscard]] constexpr bool Div(const LhsT &lhs, const RhsT &rhs)
{
    // TODO: Implement

    return false;
}





/**
 * @brief Checks if an assignment causes integer overflow.
 *        Should work in any implementation.
 *
 * @tparam LhsT Left-hand operand's integral type
 * @tparam RhsT Right-hand operand's integral type
 * @param lhs Left-hand operand
 * @param rhs Right-hand operand
 * @return true Causes integer overflow
 * @return false Does not cause integer overflow
 */
template <std::integral LhsT, std::integral RhsT>
[[nodiscard]] constexpr bool Assign(const RhsT &rhs)
{
    return rhs > std::numeric_limits<LhsT>::max()
           || rhs < std::numeric_limits<LhsT>::min();
}

} // namespace overflow::checks

#endif // #ifndef OVERFLOWWRAPPER_SRC_OVERFLOW_CHECKS_HPP