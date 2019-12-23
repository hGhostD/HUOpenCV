//
//  FourthClass.cpp
//  HUOpenCV4
//
//  Created by hu on 2019/12/18.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "FourthClass.hpp"
#include <opencv.hpp>
using namespace cv;
using namespace std;

void mat_test() {
    cv::Mat mat(300, 1000, 3.f, CV_32FC3);
    mat.setTo(cv::Scalar(127.f, 255.f, 0.f));
    cv::imshow("mat", mat);
    cv::waitKey();
}

void mat_copy() {
    cv::Mat apple = cv::imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    cv::Range range(100, 100);
    // Rect
    cv::Rect rect(10, 10, 200, 200);
    cv::Mat mat(apple, rect);
    cv::imshow("rect", mat);
    // Range
    cv::Range rangeRow(10, 210);
    cv::Range rangeCol(10, 210);
    cv::Mat matRange(apple, rangeRow, rangeCol);
    cv::imshow("range", matRange);
    
    cout << (int)apple.at<cv::Vec3b>(10, 10)[0] << endl;
    cout << apple.at<cv::Vec3b>(10, 10)[1] << endl;
    cout << (int)apple.at<cv::Vec3b>(10, 10)[2] << endl;

    cv::waitKey();

}

void example_4_1() {
    const int n_mat_size = 5;
    const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size};
    Mat n_mat( 3, n_mat, CV_32FC1);
    
    cv::RNG rng;
    rng.fill(n_mat, cv::RNG::UNIFORM, 0.f, 1.f);
    
    const Mat* arrays[] = { &n_mat, 0 };
    Mat my_planes[1];
    NAryMatIterator it (arrays, my_planes);
}
