#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"

int main()
{

    //使用本地图片进行调试，可以成功识别(int argc, char **argv)
    // if (argc < 2)
    // {
    //     std::cerr << "Usage: " << argv[0] << " <input_image>\n";
    //     return 1;
    // }
    // std::string inPath = argv[1];
    // cv::Mat img_ = cv::imread(inPath);


    // 初始化相机、yolo类
    
    myCamera Camera;
    auto_aim::YOLO yolo("./configs/yolo.yaml",0);
    

    while (1) {
        // 调用相机读取图像
        cv::Mat img_ = Camera.read();

        // 调用yolo识别装甲板
        std::list<auto_aim::Armor>armer_list = yolo.detect(img_);


        for(auto armer:armer_list)
        {

            tools::draw_points(img_,armer.points);

            tools::draw_text(img_,auto_aim::COLORS[armer.color]+auto_aim::ARMOR_NAMES[armer.name],armer.points[0],cv::Scalar(0,0,255));
        }
        // 显示图像
        cv::resize(img_, img_ , cv::Size(640, 480));
        cv::imshow("img", img_);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
    
    return 0;
}