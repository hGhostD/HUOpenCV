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
