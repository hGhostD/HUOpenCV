//
//  HUFifthChapterLearning.cpp
//  HUOpenCVOCTool
//
//  Created by hu on 2018/10/3.
//  Copyright © 2018 jw.hu. All rights reserved.
//

#include "HUFifthChapterLearning.hpp"
#include <cv.h>

//#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

// 模糊处理
// https://docs.opencv.org/master/dc/dd3/tutorial_gausian_median_blur_bilateral_filter.html
void cv_smooth() {
    Mat img = imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    imshow("smooth", img);
    Mat smooth;
//    blur(img, smooth, Size(50, 50));

    GaussianBlur(img, img, Size(10,10), 10);
//    imshow("after", smooth);
    waitKey();
}

void cv_erode() {
    Mat img = imread("/Users/jw.hu/Desktop/3.jpg");
    Mat erode;
    imshow("smooth", img);
    cv::erode(img, erode, Mat());
    imshow("erode", erode);
    Mat clidate;
    dilate(img, clidate, Mat());
    imshow("dilate", clidate);
    waitKey();
}

void smooth_opeartor() {
//    cv_smooth();
    cv_erode();
}
