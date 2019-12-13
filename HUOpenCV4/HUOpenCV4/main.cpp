//
//  main.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2019/12/11.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include <iostream>
#include <opencv.hpp>
#include <highgui.hpp>

int main(int argc, const char * argv[]) {
    // insert code here...
    cv::Mat img = cv::imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    if (img.empty()) {
        return -1;
    }
    
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    
    cv::imshow("Example1", img);
    cv::waitKey();
    cv::destroyAllWindows();
    
    return 0;
}
