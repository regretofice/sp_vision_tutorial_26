#ifndef AUTO_BUFF__SOLVER_HPP
#define AUTO_BUFF__SOLVER_HPP
#include <opencv2/opencv.hpp>
#include<vector>
namespace auto_buff
{
class Buff_Solver
{
public:
    cv::Point3f target_center,holder_center;
    void solvePnP(std::vector<cv::Point2f> points);
};
}  // namespace auto_buff
#endif  // SOLVER_HPP