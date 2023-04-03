//
//  Tenth.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/3/30.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "Tenth.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void createBorder() {
    cout << "第十章" << endl;
    
    Mat img = imread("/Users/hujiawen/Desktop/小程序测试图片/1.jpeg");
    Mat dst;
    
    int border = 100;
    Scalar color(255, 255, 255);
    copyMakeBorder(img, dst, border,border,border,border, cv::BORDER_CONSTANT, color);
    
    cout << img.rows << endl;
    cout << dst.rows << endl;
    
    imshow("10-1", dst);
    waitKey();
}

void threshold() {
    
    Mat lenna = imread("/Users/hujiawen/Desktop/lenna.jpg", cv::IMREAD_GRAYSCALE);
    Mat dst;
    // 150 ~ 200
    threshold(lenna, dst, 150, 200, cv::THRESH_BINARY );
    show(dst, __FUNCTION__);
    apaptive();
}

void apaptive() {
    Mat lenna = imread("/Users/hujiawen/Desktop/lenna.jpg", cv::IMREAD_GRAYSCALE);
    Mat dst;
    
    adaptiveThreshold(lenna, dst, 200, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 71, 15);
    show(dst, __FUNCTION__);
}

void show(Mat mat, const String& name) {
    String windowName = "10-" + name;
    imshow(windowName, mat);
    waitKey(0);
}
