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

void showImage(const char* fileName) {

    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
//    IplImage *img = cvLoadImage(fileName, CV_LOAD_IMAGE_ANYCOLOR);
    IplImage *img = cvLoadImage("/Users/jw.hu/Desktop/images.jpg", CV_LOAD_IMAGE_ANYCOLOR);
    
    cvShowImage("image", img);
    cvWaitKey(0);
    
    cvReleaseImage(&img);
    cvDestroyWindow("image");
}

