//
//  Fourteenth.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/10/25.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "Fourteenth.hpp"

namespace chapter_14 {
void test() {
    cv::Mat mat = cv::imread("/Users/hujiawen/Desktop/OpenCV_Source/pic3.png", 1);
    cv::Mat dst;
    cv::cvtColor(mat, dst, cv::COLOR_BGRA2GRAY);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Canny(dst, dst, 50, 200);
    cv::findContours(dst, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    
//    std::cout << hierarchy.size() << std::endl;
    cv::Mat white = cv::Mat(mat.size(), CV_8UC3, cv::Scalar(255, 255, 255));
    cv::drawContours(white, contours, -1, cv::Scalar(0, 0, 255));
    
    cv::imshow("canny", white);
    cv::waitKey();
}

int value = 0;
cv::Mat g_gray, g_binary;
void on_tracker(int, void *) {
    cv::threshold(g_gray, g_binary, value, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point>> con;
    cv::findContours(g_binary, con, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    g_binary = cv::Scalar::all(0);
    
    cv::drawContours(g_binary, con, -1, cv::Scalar::all(255));
    cv::imshow("win", g_binary);
}

void test_14_1() {
    cv::Mat mat = cv::imread("/Users/hujiawen/Desktop/OpenCV_Source/pic3.png", 0);
    g_gray = mat;
    cv::namedWindow("win");
    cv::createTrackbar("track", "win", &value, 254, on_tracker);
    on_tracker(0, 0);
    cv::waitKey();
}


void test_convexHUll() {
    cv::Mat mat = cv::imread("/Users/hujiawen/Desktop/1.jpg", 0);
    cv::Canny(mat, mat, 100, 200);
    
    std::vector<std::vector<cv::Point>> con;
    
    cv::findContours(mat, con, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    
    double arc = cv::arcLength(con[0], true);
    
    std::cout << arc << std::endl;
    cv::imshow("win", mat);
    cv::waitKey();
}

}
