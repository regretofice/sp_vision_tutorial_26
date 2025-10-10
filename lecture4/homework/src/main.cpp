#include "tasks/buff_detector.hpp"
#include "io/camera.hpp"
#include <chrono>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include "tasks/buff_solver.hpp"
#include "tools/plotter.hpp"
int main()
{
    io::Camera camera(2.5, 16.9, "2bdf:0001");
    std::chrono::steady_clock::time_point timestamp;  
    auto_buff::Buff_Detector detector;
    tools::Plotter plotter;
    auto_buff::Buff_Solver buff_solver;
    while(true){
        cv::Mat img;
        
        camera.read(img, timestamp);
        
        auto fanblades = detector.detect(img);
        //得到的是“一个扇叶的运动轨迹”，不是“很多个”扇叶
        //kpt存着所有关键点，其中kpt[4]是圆环中心
        cv::Mat display_img = img.clone();
        cv::resize(display_img,display_img,{},0.8,0.8);
        cv::imshow("Detection Results", display_img);    
        if (cv::waitKey(30) == 27) { // 按ESC键退出
            break;
        }
        //非常必要，否则会非法访问
        if(fanblades.empty()){
            std::cout << "未检测到扇叶" << std::endl;
            continue;
        }
        else
        {
            std::cout << "检测到扇叶" << std::endl;
            buff_solver.solvePnP(fanblades.begin()->points);
        }

        nlohmann::json data;
        if(buff_solver.target_center.x)
        {
            data["fanblade_target_center_X"] = buff_solver.target_center.x;
        }
        if(buff_solver.target_center.y)
        {
            data["fanblade_target_center_Y"] = buff_solver.target_center.y;
        }
        if(buff_solver.target_center.z)
        {
            data["fanblade_target_center_Z"] = buff_solver.target_center.z;
        }
        if(buff_solver.holder_center.x)
        {
            data["fanblade_holder_center_X"] = buff_solver.holder_center.x;
        }
        if(buff_solver.holder_center.y)
        {
            data["fanblade_holder_center_Y"] = buff_solver.holder_center.y;
        }
        if(buff_solver.holder_center.z)
        {
            data["fanblade_holder_center_Z"] = buff_solver.holder_center.z;
        }
        plotter.plot(data);

        
        
    }
    cv::destroyAllWindows();
    return 0;
}