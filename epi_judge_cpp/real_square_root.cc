#include "test_framework/generic_test.h"
#include <algorithm>

using namespace std;

bool IsEqual(double a, double b) {
  return fabs(a - b) / max(a, b) <= numeric_limits<double>::epsilon();
}

double SquareRoot(double x)
{
  double lower = 0;
  double upper = max(x, 1.0);
  double sqrt = lower + 0.5 * (upper - lower);
  double sqrt_squared;
  double epsilon = 1e-9;
  while (!IsEqual((sqrt_squared = sqrt * sqrt), x)) {
    if (sqrt_squared > x) {
      upper = sqrt;
    } else  {
      lower = sqrt;
    }
    sqrt = lower + 0.5 * (upper - lower);
  }
  return sqrt;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
