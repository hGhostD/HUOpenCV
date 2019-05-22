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
#include "S2iReflective.hpp"

using namespace std;
using namespace cv;

void callback(int event, int x, int y, int flags, void* param) {
    if (event == CV_EVENT_LBUTTONDOWN) {
        // 获取图片坐标点
        cout << x << ":" << y << endl;
    }
}

void param(double &a, double &b, double &c, Point p1, Point p2) {
    
    double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
    
    a = y2 - y1;
    b = x1 - x2;
    c = (x2 - x1) * y1 - (y2 - y1) * x1;
    if (b < 0) {
        a *= -1; b *= -1; c *= -1;
    } else if (b == 0 && a < 0) {
        a *= -1; c *= -1;
    }
}

Point getIntersectPoint(double a1, double b1, double c1,double a2, double b2, double c2) {
    double m =  a1 * b2 - a2 * b1;
    if (m == 0) {
        return cvPoint(-1, -1);
    }
    double x = (c2 * b1 - c1 * b2) / m;
    double y = (c1 * a2 - c2 * a1) / m;
    return cvPoint(x, y);
}




int main(int argc, const char * argv[]) {
//    vector<Point> points;
//    Point p1 = cvPoint(0, 0);
//    Point p2 = cvPoint(100, 0);
//    Point p3 = cvPoint(100, 200);
//    Point p4 = cvPoint(0, 100);
//
//    points.push_back(p1);
//    points.push_back(p2);
//    points.push_back(p3);
//    points.push_back(p4);
//
//    double a,b,c = 0;
//    double d,e,f = 0;
//    param(a, b, c, p1, p3);
//    param(d, e, f, p2, p4);
//
//    Point point = getIntersectPoint(a, b, c, d, e, f);
//
//    cout << a << " " << b << " " << c << endl
//    << point << endl;
//    s2iImageoperator();
//    findS();
    imageClarity();
//    get_center_point_array(points);
//    drawLine();
//    fourth_first_b();
//    fourth_third();
//    IplImage* img = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/smarties.png");
//    light(img);
    
//    s2iImageoperator();
    
    return 0;
}




