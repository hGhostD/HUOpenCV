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
    cvNamedWindow(name, CV_WINDOW_AUTOSIZE);
    CvCapture* capture;
    IplImage* frame;
    if (strcmp(name, "camera") == 0) {
        capture = cvCreateCameraCapture(0);
    } else {
        capture = cvCreateFileCapture(name);
    }
    assert(capture != NULL);
    while (1) {
        frame = cvQueryFrame(capture);
        if (!frame) break;
        cvShowImage("Ex2", frame);
        char c = cvWaitKey(33);
        if (c == 27) break;
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow(name);
}
