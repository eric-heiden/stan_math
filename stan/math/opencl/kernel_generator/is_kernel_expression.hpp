#ifndef STAN_MATH_OPENCL_KERNEL_GENERATOR_IS_KERNEL_EXPRESSION_HPP
#define STAN_MATH_OPENCL_KERNEL_GENERATOR_IS_KERNEL_EXPRESSION_HPP
#ifdef STAN_OPENCL

#include <stan/math/opencl/is_matrix_cl.hpp>
#include <stan/math/prim/meta.hpp>
#include <type_traits>

namespace stan {
namespace math {

/** \addtogroup opencl_kernel_generator
 *  @{
 */
/**
 * Non-templated base of \c operation is needed for easy checking if something
 * is a subclass of \c operation.
 */
class operation_cl_base {};

/**
 * Determines whether a type is non-scalar type that is a valid kernel generator
 * expression.
 */
template <typename T, typename = void>
struct is_kernel_expression_and_not_scalar
    : bool_constant<std::is_base_of<operation_cl_base,
                                    std::remove_reference_t<T>>::value> {};

template <typename T>
struct is_kernel_expression_and_not_scalar<T, require_matrix_cl_t<T>>
    : std::true_type {};

/**
 * Determines whether a type is is a valid kernel generator expression. Valid
 * expressions are kernel generator operations, scalars and \c matrix_cl and
 * references of these types.
 */
template <typename T>
struct is_kernel_expression
    : bool_constant<is_kernel_expression_and_not_scalar<T>::value
                    || std::is_arithmetic<std::remove_reference_t<T>>::value> {
};

/**
 * Enables a template if all given types are non-scalar types that are a
 * valid kernel generator expressions.
 */
template <typename... Types>
using require_all_kernel_expressions_and_none_scalar_t
    = require_all_t<is_kernel_expression_and_not_scalar<Types>...>;

/**
 * Enables a template if all given types are are a valid kernel generator
 * expressions.
 */
template <typename... Types>
using require_all_kernel_expressions_t
    = require_all_t<is_kernel_expression<Types>...>;
/** @}*/
}  // namespace math
}  // namespace stan

#endif
#endif
