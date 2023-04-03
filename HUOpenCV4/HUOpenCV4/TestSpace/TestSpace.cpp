//
//  TestSpace.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/3/28.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "TestSpace.hpp"
#include <opencv.hpp>

using namespace cv;
using namespace std;

void detect_sharpness() {
    
    Mat img = imread("/Users/hujiawen/Desktop/小程序测试图片/1.jpeg");
    Mat dst, lap;
    
    Scalar mu,stddev;
    
    cvtColor(img, dst, COLOR_RGB2GRAY);
    
    Laplacian(dst, lap, CV_64F);
    meanStdDev(lap, mu, stddev);
    
    int r;
    r = stddev.val[0];
    
    cout << r * r << endl;
//    cout << (int)stddev.val[0] << endl;
    
}
