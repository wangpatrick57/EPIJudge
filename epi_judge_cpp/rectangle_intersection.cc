#include <tuple>
#include <algorithm>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"

using namespace std;

struct Rect
{
    int x, y, width, height;
};

Rect IntersectRectangle(const Rect &r1, const Rect &r2)
{
    int intersect_left_x = max(r1.x, r2.x);
    int intersect_right_x = min(r1.x + r1.width, r2.x + r2.width);
    int intersect_width = intersect_right_x - intersect_left_x;

    int intersect_top_y = max(r1.y, r2.y);
    int intersect_bottom_y = min(r1.y + r1.height, r2.y + r2.height);
    int intersect_height = intersect_bottom_y - intersect_top_y;

    if (intersect_width < 0 || intersect_height < 0) {
        return {0, 0, -1, -1};
    }

    return {intersect_left_x, intersect_top_y, intersect_width, intersect_height};
}
bool operator==(const Rect &r1, const Rect &r2)
{
    return std::tie(r1.x, r1.y, r1.width, r1.height) ==
           std::tie(r2.x, r2.y, r2.width, r2.height);
}

namespace test_framework
{
    template <>
    struct SerializationTrait<Rect> : UserSerTrait<Rect, int, int, int, int>
    {
        static std::vector<std::string> GetMetricNames(const std::string &arg_name)
        {
            return {FmtStr("height({})", arg_name), FmtStr("width({})", arg_name)};
        }

        static std::vector<int> GetMetrics(const Rect &x)
        {
            return {x.height, x.width};
        }
    };
} // namespace test_framework

std::ostream &operator<<(std::ostream &out, const Rect &r)
{
    return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"r1", "r2"};
    return GenericTestMain(args, "rectangle_intersection.cc",
                           "rectangle_intersection.tsv", &IntersectRectangle,
                           DefaultComparator{}, param_names);
}
