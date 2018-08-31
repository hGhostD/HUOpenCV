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

void alphablend(const char* fileName1, const char* fileName2, const char* alp_x, const char* alp_y, const char* alp_width, const char* alp_height, const char* alp, const char* alp_beta) {
    IplImage* src1 = cvLoadImage(fileName1);
    IplImage* src2 = cvLoadImage(fileName2);
    if (src1 !=0 && src2 != 0) {
        int x = atoi(alp_x);
        int y = atoi(alp_y);
        int width = atoi(alp_width);
        int height = atoi(alp_height);
        double alpha = (double)atof(alp);
        double beta = (double)atof(alp_beta);
        cvSetImageROI(src1, cvRect(x, y, width, height));
        cvSetImageROI(src2, cvRect(0, 0, width, height));
        cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
        cvResetImageROI(src1);
        cvNamedWindow("Alpha_blend", 1);
        cvShowImage("Alpha_blend", src1);
        cvWaitKey();
    }
    
    
}
