//
//  SecondClass.hpp
//  HUOpenCV4
//
//  Created by jw.hu on 2019/12/13.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#ifndef SecondClass_hpp
#define SecondClass_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

void showImage();
void showVideo();
void sliderVideo();
void exapmple2_5(const cv::Mat &image);
void pyr_test(const cv::Mat &image);
void canny_test(const cv::Mat &image);
void camera_test();
void write_test(const cv::String &filename);

#endif /* SecondClass_hpp */
