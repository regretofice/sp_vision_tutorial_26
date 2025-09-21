#include"tools.hpp"
cv::Mat resize_img(const cv::Mat src_img,const int img_width,const int img_height)
{
    //实现图片等比例缩放
    double scale = std::min((double)img_width/src_img.cols,(double)img_height/src_img.rows);
    fmt::print("The scaling ratio of the image is {}\n",scale);

    int resized_width = (int)(src_img.cols * scale);
    int resized_height = (int)(src_img.rows * scale);
    cv::Mat resized_img;
    cv::resize(src_img,resized_img,cv::Size(resized_width,resized_height));

    //黑色边框填充图片边缘
    int left_padding = (img_width - resized_width)/2;
    int right_padding = img_width - resized_width -left_padding;
    int top_padding = (img_height - resized_height)/2;
    int bottom_padding = img_height - resized_height - top_padding;
    fmt::print("The top of the image is filled with {} pixel.\n",top_padding);
    fmt::print("The bottom of the image is filled with {} pixel.\n",bottom_padding);
    fmt::print("The left of the image is filled with {} pixel.\n",left_padding);
    fmt::print("The right of the image is filled with {} pixel.\n",right_padding);

    cv::Mat padded_img;
    cv::copyMakeBorder(resized_img,padded_img,top_padding,bottom_padding,left_padding,right_padding,cv::BORDER_CONSTANT,cv::Scalar(0));

    return padded_img;
}