//
//  main.m
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2018/8/28.
//  Copyright © 2018年 jw.hu. All rights reserved.
//
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "HUPlayAVITool.hpp"

using namespace std;
using namespace cv;

void example(IplImage* image);

IplImage* doPyrDown(
                    IplImage* in, int filter = CV_GAUSSIAN_5x5
                    ) {
//    assert(in->width % 2 == 0 && in->height % 2 == 0);
    IplImage* out = cvCreateImage(cvSize(in->width / 2, in -> height / 2), in->depth, in->nChannels);
    cvPyrDown(in, out);
    return out;
}

int main(int argc, const char * argv[]) {
    
    playAVI("~/Desktop/OpenCV_Source/tree.avi");
    
    return 0;
}

void example(IplImage* image) {
    
    cvNamedWindow("Ex4");
    
    cvNamedWindow("Ex4-out");
    
    
    cvShowImage("image", image);
    
    IplImage* out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
    
    cvSmooth(image, out, CV_GAUSSIAN, 3, 3);
    
    cvShowImage("Ex4-out", out);
    
    cvReleaseImage(&out);
    
    cvWaitKey(0);
    
    cvDestroyWindow("Ex4");
    cvDestroyWindow("Ex4-out");
    
}

