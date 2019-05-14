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
 https://blog.csdn.net/luoshixian099/article/details/41422099
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
    cvCanny(grey, canny, 30, 100);
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

void fourth_first_b() {
    IplImage* img = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/smarties.png");
    IplImage* gray = cvCreateImage(cvGetSize(img), img->depth, 1);
    IplImage* canny = cvCloneImage(gray);
    // 转成灰度图片
    cvConvertImage(img, gray);
    // Canndy 边缘检测
    cvCanny(gray, canny, 30, 100);
    
    int width = img->width;
    int height = img->height;
    // 创建画布图片和图片头
    IplImage *unit = cvCreateImage(cvSize(width * 3, height), img->depth, 3);
    IplImage *imag_header = cvCreateImageHeader(cvSize(width, height), img->depth, 3);
    imag_header->widthStep = unit->widthStep;
    imag_header->imageData = unit->imageData;
    // 将第一张图片复制到 unit 上
    cvCopy(img, imag_header);
    // 处理灰色图片
    IplImage *grey_imag = cvCreateImage(cvSize(width, height), img->depth, 3);
    cvConvertImage(gray, grey_imag, CV_GRAY2BGR);
    imag_header->imageData = unit->imageData + img->widthStep;
    cvCopy(grey_imag, imag_header);
    // 处理边缘图片
    IplImage *canny_imag = cvCreateImage(cvSize(width, height), img->depth, 3);
    cvConvertImage(canny, canny_imag, CV_GRAY2BGR);
    imag_header->imageData = unit->imageData + img->widthStep * 2;
    cvCopy(canny_imag, imag_header);
    
    // 添加文字
    CvFont m_font;
    cvInitFont(&m_font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0);
    cvPutText(unit, "Origin", cvPoint(0, 10), &m_font, cvScalar(255,255,0));
    cvPutText(unit, "中文", cvPoint(200, 200), &m_font, cvScalar(255,255,0));
    cvPutText(unit, "Center", cvPoint(width / 2, height / 2), &m_font, cvScalar(255,255,0));
    
    
    // 显示图片
    cvNamedWindow("Ex4-1 b");
    cvShowImage("Ex4-1 b", unit);
    while (1) { if (cvWaitKey(100) == 27) { break; } }
    cvDestroyAllWindows();
}
// 4-2
void showpiexl(IplImage* img, int x, int y);
void mouseCallBack( int event, int x, int y, int flags, void* param) {
    IplImage* img0;
    img0 = (IplImage *)param;
    switch (event) {
        case CV_EVENT_LBUTTONDOWN:
            //
            showpiexl(img0, x, y);
            break;
            
        default:
            break;
    }
}


void fourth_second() {
    IplImage* image = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/smarties.png");
    
    cvNamedWindow("EX4-2");
    cvShowImage("EX4-2", image);
   
    cvSetMouseCallback("EX4-2", mouseCallBack, (void *)image);
    while (1) { if (cvWaitKey(100) == 27) { break; } }
    cvDestroyAllWindows();
    cvReleaseImage(&image);
}

void showpiexl(IplImage* img, int x, int y) {
    CvScalar rgb = cvGet2D(img, y, x);
    char label[40];
    sprintf(label, "(%f, %f, %f)", rgb.val[2], rgb.val[1], rgb.val[0]);
    
    CvFont font;
    cvInitFont(&font, CV_FONT_VECTOR0, 1, 1, 0, 1, 8);
    cvPutText(img, label, cvPoint(x, y), &font,cvGet2D(img, y, x));
    cvShowImage("EX4-2", img);
}

CvPoint p1;
CvPoint p2;
void drawRect(IplImage *img) {
    CvPoint pt1 = cvPoint(MIN(p1.x, p1.x), MIN(p1.y, p1.y));
    CvPoint pt2 = cvPoint(MIN(p2.x, p2.x), MIN(p2.y, p2.y));
    cvRectangle(img, pt1, pt2, cvScalar(255, 176, 0));
}
void mouse4_3(int event, int x, int y, int flags, void* param) {
    IplImage* img = (IplImage *)param;
    switch (event) {
        case CV_EVENT_LBUTTONDOWN:
            p1 = cvPoint(x, y);
//            cvRectangleR(img, cvRect(0, 0, 100, 100), CvScalar(255,176,0));
            break;
        case CV_EVENT_LBUTTONUP:
            p2 = cvPoint(x, y);
            drawRect(img);
            break;
        default:
            break;
    }
}


void fourth_third() {
    IplImage* img = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/orange.jpg");
    cvNamedWindow("4-3");
    cvShowImage("4-3", img);
    cvSetMouseCallback("4-3", mouse4_3, (void *)img);

    while (1) {
        if (cvWaitKey(100) == 27) { break; }
//        cvShowImage("4-3", img);
    }
    cvDestroyAllWindows();
}
