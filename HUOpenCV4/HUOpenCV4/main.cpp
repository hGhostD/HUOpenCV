//
//  main.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2019/12/11.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include <iostream>
#include <opencv.hpp>
#include "SecondClass.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
//    showImage();
    cv::Mat img = cv::imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    exapmple2_5(img);
    return 0;
}
