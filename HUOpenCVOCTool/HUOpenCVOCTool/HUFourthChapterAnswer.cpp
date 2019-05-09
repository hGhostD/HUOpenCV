//
//  HUFourthChapterAnswer.cpp
//  HUOpenCVOCTool
//
//  Created by hu on 2018/9/19.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#include "HUFourthChapterAnswer.hpp"
#include <iostream>
#include <highgui.h>
#include <cv.h>
/*
 书后第四章习题
 */

void fourth_first() {
//    CvCapture* video = cvCreateFileCapture("/Users/jw.hu/Desktop/tree.avi");
//    CvCapture* video = cvCreateCameraCapture(0);
//    CV_Assert(video);
    
//    IplImage* frame = cvQueryFrame(video);
    IplImage* img = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/smarties.png");
    IplImage* grey = cvCreateImage(cvGetSize(img), img->depth, 1);
    IplImage* canny = cvCloneImage(grey);
    // 转成灰度图片
    cvConvertImage(img, grey);
    // Canndy 边缘检测
    cvCanny(grey, canny, 100, 200);
    // 显示图片
    cvNamedWindow("Ex4-1 A");
    cvNamedWindow("Ex4-1 B");
    cvNamedWindow("Ex4-1 C");
    
    cvShowImage("Ex4-1 A", img);
    cvShowImage("Ex4-1 B", grey);
    cvShowImage("Ex4-1 C", canny);
    
    cvMoveWindow("Ex4-1 A", 0, 0);
    cvMoveWindow("Ex4-1 B", img->width, 0);
    cvMoveWindow("Ex4-1 C", img->width * 2, 0);

    
    while (1) { if (cvWaitKey(100) == 27) { break; } }
    cvDestroyAllWindows();
}
// 4-2
void showpiexl(IplImage* img, int x, int y);
void mouseCallBack( int event, int x, int y, int flags, void* param) {
    IplImage* img0;
    img0 = (IplImage *)param;
    switch (event) {
        case CV_EVENT_LBUTTONUP:
            
            //
            showpiexl(img0, x, y);
            break;
            
        default:
            break;
    }
}


void fourth_second(const char* fileName) {
    
    IplImage* image = cvLoadImage(fileName);
    
    cvNamedWindow("EX4-2");
    cvShowImage("EX4-2", image);
   
    cvSetMouseCallback("EX4-2", mouseCallBack, (void *)image);
    while (1) { if (cvWaitKey(100) == 27) { break; } }
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
