//
//  TwelfthClass.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/5/6.
//  Copyright © 2023 jw.hu. All rights reserved.
//

/**
 
 
 */

#include "TwelfthClass.hpp"

namespace chapter_12 {

inline cv::Mat lenna() {
    return cv::imread("/Users/hujiawen/Desktop/lenna.jpg");
}

void show() {
//    cv::Mat lenna = cv::imread("/Users/hujiawen/Desktop/lenna.jpg");
//    cv::imshow("12", lenna);
//    cv::waitKey();
    cv::Mat src(1000, 1000, CV_8UC3);
    
    cv::putText(src, "hello", cv::Point2f(100, 200), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(0,0,255));
    cv::imshow("text", src);
    cv::waitKey();
}



void test() {
}

}
