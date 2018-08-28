//
//  HUPlayAVITool.cpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2018/8/28.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#include <highgui.h>
#include "HUPlayAVITool.hpp"

void playAVI(const char* name) {
    cvNamedWindow("Ex2", CV_WINDOW_AUTOSIZE);
    CvCapture* capture = cvCreateFileCapture(name);
    IplImage* frame;
    while (1) {
        frame = cvQueryFrame(capture);
        if (!frame) break;
        cvShowImage("Ex2", frame);
        char c = cvWaitKey(33);
        if (c == 27) break;
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("Ex2");
}
