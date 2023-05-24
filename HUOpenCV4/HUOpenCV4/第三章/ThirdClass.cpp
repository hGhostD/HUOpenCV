//
//  ThirdClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2019/12/17.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "ThirdClass.hpp"
#include <iostream>
#include <opencv.hpp>

using namespace std;

namespace chapter_03 {

void learn() {
    cv::RNG rng;
    int a = rng.uniform(0, 100);
    int b = rng.next();
    cout << a << endl << b << endl;
}

void test_01() {
    double x = -1.56;
    
    cout << cv::abs(x) << endl;
    cout << cvRound(x) << endl;
    cout << cvFloor(x) << endl;
    cout << cvCeil(x) << endl;
    
    cv::RNG rng(time(0));
    int r = rng.uniform(0, 256);
    cout << "rng:" << r << endl;
    
    cv::Point2f pf(1.0, 2.0);
    cv::Point p(pf);
    cout << p.x << "," << p.y << endl;
    cv::Point2d pd(p);
    cout << pd.x << "," << pd.y << endl;
    
//    int color = (int)rng;
//    cv::Scalar s = cv::Scalar(color & 255, (color >> 8)&255, (color >> 16)&255);
////    cout << "color:" << color & 255 << endl;
//    cv::Mat mat = cv::Mat(100, 100, CV_8UC3, s);
//    cv::imshow("rng", mat);
//    cv::waitKey(3000);
}

void test_02() {
    cv::Matx33f matx(1,2,3,4,5,6,7,8,9);
    cout << matx << endl;
    cv::Vec3f v3(1,2,3);
    cout << v3 << endl;
    
    cout << matx * v3 << endl;
    
//    int d[] = {1,2,3,4,5,6,7,8,9};
//    int *d = {1,2,3,4,5,6,7,8,9};
    cv::Mat m(3, 3, CV_8U, (int []){1,2,3,4,5,6,7,8,9});
    cv::Mat_<double> mat(3, 1);
    mat << 1,2,3;
    cout << mat << endl;
    
}

void test() {
//    test_01();
    test_02();
}
}
