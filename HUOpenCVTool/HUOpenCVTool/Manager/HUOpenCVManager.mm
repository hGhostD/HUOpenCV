//
//  HUOpenCVManager.m
//  HUOpenCV
//
//  Created by jw.hu on 2018/7/25.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#import "HUOpenCVManager.h"
#import <AppKit/AppKit.h>
#include "HUTool.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

IplImage* example2_4(IplImage* image);
@implementation HUOpenCVManager

+ (NSString *)openCVVersionString {
//    showImage("/Users/jw.hu/Desktop/images.jpg");

    return [NSString stringWithFormat:@"OpenCV Version %s",  CV_VERSION];
}

+ (NSInteger)objGetVideoWidth:(NSString *)fileName {
//    IplImage* image = cvLoadImage([fileName cStringUsingEncoding:NSASCIIStringEncoding]);
    IplImage* image = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/pic1.png");
    IplImage* newImg = example2_4(image);
    return newImg->width;
}
@end

IplImage* example2_4(IplImage* image) {
    IplImage* outImg = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
    cvSmooth(image, outImg, CV_GAUSSIAN, 3, 3);
    
    cvReleaseImage(&outImg);
    return outImg;
}
