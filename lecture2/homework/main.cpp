#include<opencv2/opencv.hpp>
#include<fmt/format.h>
#include"tools.hpp"
int main(int argc, char **argv)
{
    
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_image>\n";
        return 1;
    }
    std::string inPath = argv[1];
    fmt::print("Input image path: {}\n",inPath);
    cv::Mat src_img = cv::imread(inPath);
    if(src_img.empty())
    {
        fmt::print("fail to load image\n");
        return -1;
    }
    //读入结束

    cv::Mat dst_img = resize_img(src_img,640,640);
    // cv::imshow("src_img",src_img);
    cv::imshow("padded_image",dst_img);
    cv::waitKey(0);
    return 0;
}