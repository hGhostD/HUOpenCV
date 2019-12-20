//
//  FourthClass.cpp
//  HUOpenCV4
//
//  Created by hu on 2019/12/18.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "FourthClass.hpp"
#include <opencv.hpp>

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
    cv::waitKey();

}
