//
//  main.m
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2018/8/28.
//  Copyright © 2018年 jw.hu. All rights reserved.
//
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
    
    //这里要填写你要显示的图片路径
    IplImage *img = cvLoadImage("/Users/jw.hu/Desktop/images.jpg", CV_LOAD_IMAGE_ANYCOLOR);
    
    cvShowImage("image", img);
    
    cvWaitKey(0);
    
    cvReleaseImage(&img);
    
    cvDestroyWindow("image");
    
    return 0;
}
