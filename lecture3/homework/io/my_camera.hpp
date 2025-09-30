#include "hikrobot/include/MvCameraControl.h"
#include <opencv2/opencv.hpp>

class myCamera
{
private:
    void * handle_=NULL;
    int ret_;
    MV_CC_DEVICE_INFO_LIST device_list_;
    cv::Mat transfer(MV_FRAME_OUT& raw);
public:
    myCamera();
    cv::Mat read();
    ~myCamera();
};