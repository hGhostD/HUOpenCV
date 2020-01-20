//
//  FifthClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2020/1/20.
//  Copyright © 2020 jw.hu. All rights reserved.
//

#include "FifthClass.hpp"
#include <opencv.hpp>
using namespace cv;
using namespace std;

void learn_abs() {

    Mat a = Mat::ones(100, 100, CV_32FC1);
    Mat b = Mat::zeros(100, 100, CV_32FC1);
    uchar m = cv::abs(a - b);
    
    cout << a << endl;
    cout << b << endl;
    cout << m << endl;
    
}
