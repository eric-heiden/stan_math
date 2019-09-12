#ifndef STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_CCDF_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_CCDF_LOG_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_lccdf.hpp>

namespace stan {
namespace math {

/**
 * @deprecated use <code>neg_binomial_lccdf</code>
 */
template <typename T_n, typename T_shape, typename T_inv_scale>
inline auto neg_binomial_ccdf_log(const T_n& n, const T_shape& alpha,
                                  const T_inv_scale& beta) {
  return neg_binomial_lccdf(n, alpha, beta);
}

}  // namespace math
}  // namespace stan
#endif
