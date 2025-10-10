#include "buff_solver.hpp"


namespace auto_buff
{

//  相机内参(每个相机不一样)
static const cv::Mat camera_matrix =
    (cv::Mat_<double>(3, 3) <<  1776.9477196851155, 0, 756.31235265560952, 0, 1776.0591253569607, 566.16539069551641, 0, 0, 1                  );
// 畸变系数(每个相机不一样)
static const cv::Mat distort_coeffs =
    (cv::Mat_<double>(1, 5) << -0.08382326954462313, 0.097449270330296239, -0.0012558283068959985, 0.0037372210254148081, 0);


static const double TARGET_RADIUS = 0.15;//圆靶半径，单位m
static const double BULLSEYE2LIGHT = 0.52;//靶心到灯条末端距离，单位m
static const double HOLDER_RADIUS = 0.7;//靶心到旋转中心距离，单位m
static const std::vector<cv::Point3f> object_points {
    //靶标上6个点的物体坐标系坐标
    {0,-TARGET_RADIUS, 0 },  // 点 0
    {-TARGET_RADIUS,0, 0 },  // 点 1
    {0, TARGET_RADIUS, 0 },  // 点 2
    { TARGET_RADIUS,0, 0 },  // 点 3
    {       0      ,0, 0 },  // 点 4(靶心)
    {0,BULLSEYE2LIGHT, 0 }   // 点 5(灯条末端)
};
void Buff_Solver::solvePnP(std::vector<cv::Point2f> points){

    cv::Mat rvec, tvec;
    if(points.size()!=6)
    {
        std::cerr<<"points size != 6"<<std::endl;
        return;
    }

    cv::solvePnP(object_points,points,camera_matrix , distort_coeffs, rvec, tvec);

    //靶心坐标(相机坐标系下的坐标)
    target_center.x=tvec.at<double>(0);
    target_center.y=tvec.at<double>(1);
    target_center.z=tvec.at<double>(2);
    
    // 将旋转向量转换为旋转矩阵R
    cv::Mat R;
    cv::Rodrigues(rvec, R);
    
    // "旋转中心"物体坐标系坐标
    cv::Mat holder_object_point = (cv::Mat_<double>(3, 1) << 0,HOLDER_RADIUS,0);
    
    cv::Mat holder_camera_point = R * holder_object_point + tvec;
    holder_center.x = holder_camera_point.at<double>(0);
    holder_center.y = holder_camera_point.at<double>(1);
    holder_center.z = holder_camera_point.at<double>(2);
}

}  // namespace auto_buff
