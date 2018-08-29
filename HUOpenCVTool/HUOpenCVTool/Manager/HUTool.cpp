//
//  HUTool.cpp
//  HUOpenCVTool
//
//  Created by jw.hu on 2018/8/28.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#include "HUTool.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class VideoSilicing {
public:
    static int processVideo(char const *fileName);
    static int getVideoWidth(char const *fileName);
    static int getVideoHeight(char const *fileName);
};

void showImage(const char* fileName) {

    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
//    IplImage *img = cvLoadImage(fileName, CV_LOAD_IMAGE_ANYCOLOR);
    IplImage *img = cvLoadImage("/Users/jw.hu/Desktop/images.jpg", CV_LOAD_IMAGE_ANYCOLOR);
    
    cvShowImage("image", img);
    cvWaitKey(0);
    
    cvReleaseImage(&img);
    cvDestroyWindow("image");

}

int VideoSilicing::processVideo(char const *fileName){
    
    //to do code
    
    return 0;
}

int VideoSilicing::getVideoWidth(char const *fileName){
    int width = 0;
    
    //to do code
    
    return width;
}

int VideoSilicing::getVideoHeight(char const *fileName){
    cv::VideoCapture capture(fileName); // open file
    
    int height = 0;
    
    //to do code
    
    return height;
}
