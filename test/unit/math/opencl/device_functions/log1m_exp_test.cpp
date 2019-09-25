#ifdef STAN_OPENCL
#include <stan/math.hpp>
#include <stan/math/opencl/device_functions/log1m_exp.hpp>
#include <stan/math/opencl/kernel_cl.hpp>
#include <gtest/gtest.h>
#include <test/unit/math/expect_near_rel.hpp>
#include <string>

static const std::string test_kernel_code
    = STRINGIFY(__kernel void test(__global double *B, __global double *A) {
        const int i = get_global_id(0);
        B[i] = log1m_exp(A[i]);
      });

const stan::math::opencl_kernels::kernel_cl<
    stan::math::opencl_kernels::out_buffer,
    stan::math::opencl_kernels::in_buffer>
    log1m_exp("test", std::vector<std::string>{
                          stan::math::opencl_kernels::log1m_exp_device_function,
                          test_kernel_code});

TEST(MathMatrixCL, log1m_exp) {
  Eigen::VectorXd a = Eigen::VectorXd::Random(1000).array() * 0.9999;

  stan::math::matrix_cl<double> a_cl(a);
  stan::math::matrix_cl<double> res_cl(1000, 1);
  log1m_exp(cl::NDRange(1000), res_cl, a_cl);
  Eigen::VectorXd res = stan::math::from_matrix_cl<-1, 1>(res_cl);

  stan::test::expect_near_rel("log1m_exp (OpenCL)", res,
                              stan::math::log1m_exp(a));
}

#endif
