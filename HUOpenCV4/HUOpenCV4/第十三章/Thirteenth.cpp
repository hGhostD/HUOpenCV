//
//  Thirteenth.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/5/16.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "Thireteenth.hpp"

namespace chapter_13 {
void test_calcHist() {
   
    cv::Mat le = cv::imread("/Users/hujiawen/Desktop/lenna.jpg");

    std::vector<cv::Mat> bgr_plane;
    cv::split(le, bgr_plane);
    cv::Mat mask;
    cv::Mat dst_b;
    cv::Mat dst_g;
    cv::Mat dst_r;
    
    int hist[1] = { 256 };
    
    float hranges[2] = { 0 , 255 };
    const float *ranges[1] = { hranges };
    cv::calcHist(&bgr_plane[0], 1, 0, cv::Mat(), dst_b, 1, hist, ranges);
    
//    cv::imshow("calcHist", dst_b);
//    cv::waitKey();
    
    std::cout << hist[0] << std::endl;
}
void test() {
    test_calcHist();
//    std::cout << "Test" << std::endl;
}

};
