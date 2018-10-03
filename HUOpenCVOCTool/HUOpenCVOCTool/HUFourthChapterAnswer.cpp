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
    CvCapture* video = cvCreateFileCapture("/Users/mac/Desktop/douyin.mpg");
//    CvCapture* video = cvCreateCameraCapture(0);
    CV_Assert(video);
    IplImage* frame = cvQueryFrame(video);
    
    IplImage* grey = cvCreateImage(cvGetSize(frame), frame->depth, 1);
    cvConvertImage(frame, grey);
}

void fourth_my_mouse_callback( int event, int x, int y, int flags, void* param);

void fourth_second(const char* fileName) {
    
    IplImage* image = cvLoadImage(fileName);
    
    cvNamedWindow("EX4-2");
    cvShowImage("Ex4-2", image);
   
    cvSetMouseCallback("EX4-2", fourth_my_mouse_callback, (void *)image);
    
    cvWaitKey();
    cvDestroyAllWindows();
    cvReleaseImage(&image);
}

void showpiexl(IplImage* img, int x, int y) {
    char label[20];
    sprintf(label, "(%d, %d, %d)", CV_IMAGE_ELEM(img, uchar, y, 3*x),
            CV_IMAGE_ELEM(img, uchar, y, 3*x+1),CV_IMAGE_ELEM(img, uchar, y, 3*x+2));
    CvFont font;
    cvInitFont(&font, CV_FONT_VECTOR0, 1, 1, 0, 1, 8);
    cvShowImage("EX4-2", img);
}

void fourth_my_mouse_callback(int event, int x, int y, int flags, void* param) {
    IplImage* img0;
    img0 = (IplImage *)param;
    switch (event) {
        case CV_EVENT_LBUTTONUP:
            showpiexl(img0, x, y);
            break;
            
        default:
            break;
    }
}
