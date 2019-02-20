#include <gtest/gtest.h>
#include <math.h>

#include "cpp_utils/interp.h"


// Declare another test
TEST(TestInterp, sine_test)
{
  std::vector<double> x = {0.1, 0.5, 1.0, 1.2, 2.2};
  std::vector<double> y;
  for(double x_i : x) {
    y.push_back(sin(x_i));
  }

  std::vector<double> x_interp = {0.3, 0.9,2.1};

  auto y_interp = cpp_utils::interp(x_interp,x,y,false);
  ASSERT_NEAR(sin(x_interp.at(0)),y_interp.at(0),0.1);
  ASSERT_NEAR(sin(x_interp.at(1)),y_interp.at(1),0.1);
  ASSERT_NEAR(sin(x_interp.at(2)),y_interp.at(2),0.1);
}

TEST(TestInterp, extrapolate_test)
{
  //y = x
  std::vector<double> x = {0.0,2.0};
  std::vector<double> y = {0.0,2.0};

  std::vector<double> x_interp = {-0.5,1.0,2.5};
  std::vector<double> y_interp = cpp_utils::interp(x_interp,x,y,true);

  ASSERT_NEAR(x_interp.at(0),y_interp.at(0),1.0e-5);
  ASSERT_NEAR(x_interp.at(1),y_interp.at(1),1.0e-5);
  ASSERT_NEAR(x_interp.at(2),y_interp.at(2),1.0e-5);

  std::vector<double> y_interp2 = cpp_utils::interp(x_interp,x,y,false);
  ASSERT_NEAR(y_interp2.at(0),0.0,1.0e-5);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
