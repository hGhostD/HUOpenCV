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
#include "HUPlayAVITool.hpp"
#include "HUChangeImageTool.hpp"
#include "HUThirdChapterAnswer.hpp"
#include "HUHighGUI.hpp"
#include "HUFourthChapterAnswer.hpp"
#include "HUFifthChapterLearning.hpp"
#include "HUFindSquares.hpp"
#include "S2iImageTest.hpp"

using namespace std;
using namespace cv;

void callback(int event, int x, int y, int flags, void* param) {
    if (event == CV_EVENT_LBUTTONDOWN) {
        // 获取图片坐标点
        cout << x << ":" << y << endl;
    }
}

int main(int argc, const char * argv[]) {
   
//    drawLine();
//    fourth_first_b();
//    fourth_third();
//    IplImage* img = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/smarties.png");
//    light(img);
    s2iImageoperator();
    return 0;
}




