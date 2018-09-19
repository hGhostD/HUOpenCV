//
//  HUFourthChapterAnswer.cpp
//  HUOpenCVOCTool
//
//  Created by hu on 2018/9/19.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#include "HUFourthChapterAnswer.hpp"
#include <highgui.h>
#include <cv.h>
/*
 书后第四章习题
 */

void fourth_first() {
    CvCapture* video = cvCreateFileCapture("/Users/mac/Desktop/tree.mov");
//    CvCapture* video = cvCreateCameraCapture(0);
    CV_Assert(video);
    IplImage* frame = cvQueryFrame(video);
    
    IplImage* grey = cvCreateImage(cvGetSize(frame), frame->depth, 1);
    cvConvertImage(frame, grey);
    
}
