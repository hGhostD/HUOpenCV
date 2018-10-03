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

void writeAVI() {
    
    cvNamedWindow( "Example2_10", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "Log_Polar", CV_WINDOW_AUTOSIZE );
    CvCapture* capture = cvCreateCameraCapture(0);
    //if (!capture){
    // return -1;
    //}
    IplImage* bgr_frame;
    double fps = cvGetCaptureProperty (
                                       capture,
                                       CV_CAP_PROP_FPS
                                       );
    printf("fps=%d\n",(int)fps);
    
    CvSize size = cvSize(
                         (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH),
                         (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT)
                         );
    
    printf("frame (w, h) = (%d, %d)\n",size.width,size.height);
#ifndef NOWRITE
    CvVideoWriter* writer = cvCreateVideoWriter(
                                                "/Users/jw.hu/Desktop/OpenCV_Source/hu.avi",
                                                CV_FOURCC('M','J','P','G'),
                                                fps,
                                                size
                                                );
#endif
    IplImage* logpolar_frame = cvCreateImage(
                                             size,
                                             IPL_DEPTH_8U,
                                             3
                                             );
    
    IplImage* gray_frame = cvCreateImage(
                                         size,
                                         IPL_DEPTH_8U,
                                         1
                                         );
    
    while( (bgr_frame=cvQueryFrame(capture)) != NULL ) {
        cvShowImage( "Example2_10", bgr_frame );
        //We never make use of this gray image
        cvConvertImage(
                       bgr_frame,
                       gray_frame,
                       CV_RGB2GRAY
                       );
        //This is just a fun conversion the mimic's the human visual system
        cvLogPolar( bgr_frame, logpolar_frame,
                   cvPoint2D32f(bgr_frame->width/2,
                                bgr_frame->height/2),
                   40,
                   CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );
        cvShowImage( "Log_Polar", logpolar_frame );
        //Sigh, on linux, depending on your ffmpeg, this often won't work ...
#ifndef NOWRITE
        cvWriteToAVI( writer, logpolar_frame );
#endif
        char c = cvWaitKey(10);
        if( c == 27 ) break;
    }
#ifndef NOWRITE
    cvReleaseVideoWriter( &writer );
#endif
    cvReleaseImage( &gray_frame );
    cvReleaseImage( &logpolar_frame );
    cvReleaseCapture( &capture );
}
