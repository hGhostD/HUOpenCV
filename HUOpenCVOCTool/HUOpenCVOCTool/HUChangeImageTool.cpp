//
//  HUChangeImageTool.cpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2018/8/29.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#include <highgui.h>
#include <cv.h>
#include "HUChangeImageTool.hpp"

IplImage* doPyrDown(IplImage* in, int filter = CV_GAUSSIAN_5x5) {
    //    assert(in->width % 2 == 0 && in->height % 2 == 0);
    IplImage* out = cvCreateImage(cvSize(in->width / 2, in -> height / 2), in->depth, in->nChannels);
    cvPyrDown(in, out);
    return out;
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


void roiAdd(const char* fileName, const char* roi_x, const char* roi_y, const char* roi_width, const char* roi_height, const char* roi_add) {
    IplImage* src = cvLoadImage(fileName);
    if(src != 0) {
        int x = atoi(roi_x);
        int y = atoi(roi_y);
        int width = atoi(roi_width);
        int heigth = atoi(roi_height);
        int add = atoi(roi_add);
        
        cvSetImageROI(src, cvRect(x, y, width, heigth));
        cvAddS(src, cvScalar(add), src);
        cvResetImageROI(src);
        cvNamedWindow("Roi_Add", 1);
        cvShowImage("Roi_Add", src);
        cvWaitKey();
    }
    
}