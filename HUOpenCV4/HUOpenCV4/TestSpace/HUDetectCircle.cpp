//
//  HUDetectCircle.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2024/2/2.
//  Copyright © 2024 jw.hu. All rights reserved.
//

#include "HUDetectCircle.hpp"

namespace HUDetect {
void detect_circle() {
//    cv::Mat mat = cv::imread("/Users/hujiawen/Desktop/Opencv_Source/coin.jpg");
    cv::Mat mat = cv::imread("/Users/hujiawen/Downloads/jiubei.jpeg");
    if (mat.empty()) {
        std::cout << "读取图片失败!!!" << std::endl;
        return;
    }
    cv::Mat img , img_edge , labels , img_color , stats;
    cv::Mat gray;
    if (mat.channels() == 3) {
        cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = mat.clone();
    }
    int filiter = 51;
    cv::GaussianBlur(gray, gray, cv::Size(filiter, filiter), 0);
    cv::threshold(gray, gray, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
    int num_components = cv::connectedComponents(gray, labels);
    
    for (auto i  = 1; i < num_components; i++) {
        cv::Mat mask = cv::Mat::zeros(gray.size(), CV_8U);
        mask.setTo(cv::Scalar(255), labels == i);
        cv::imshow("liantongyu", mask);
        cv::waitKey();
    }
    
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, 100);
//    cv::circle(gray, );
    cv::imshow("tmp", gray);
    cv::waitKey();
    cv::destroyAllWindows();
}

void houghtTest(const cv::Mat & mat) {
    /**
     1. 转灰
     2.模糊
     3.二值化
     4.轮廓
     5.找圆形
     6.过滤
     7.绘制
     */
    cv::Mat gray;
    if (mat.channels() == 3) {
        cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = mat.clone();
    }
    cv::GaussianBlur(gray, gray, cv::Size(17, 17), 0);
//    cv::threshold(gray, gray, 127, 255, cv::THRESH_BINARY+cv::THRESH_OTSU);
    std::vector<cv::Vec3f> circle;
    cv::HoughCircles(gray, circle, cv::HOUGH_GRADIENT, 1, 10);
    
    int index = 0;
    for (auto v : circle) {
        cv::Point center(cvRound(v.val[0]), cvRound(v.val[1]));
        int radius = cvRound(v.val[2]);
        
        cv::circle(mat, center, radius, cv::Scalar(0,0,255), 2);
        index++;
        cv::putText(mat, std::to_string(index), center, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255));
    }
    
    cv::imshow("detect", mat);
    cv::waitKey();
}
}
