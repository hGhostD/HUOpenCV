//
//  SixthClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2020/3/18.
//  Copyright © 2020 jw.hu. All rights reserved.
//

#include "SixthClass.hpp"
#include <opencv.hpp>
using namespace cv;
using namespace std;

void draw_line() {
    Mat backView(1000, 1000, CV_32FC3);
    
    // 画圆
    circle(backView, Point(50, 50), 50, Scalar(0, 0, 255));
    // 判断是否在线中
    Point p1 = Point(10, 10);
    Point p2 = Point(20, 20);
    bool isClipLine = clipLine(Rect(40, 40, 100, 100), p1, p2);
    cout << isClipLine << endl;  // 0
    // 画椭圆
    ellipse(backView, Point(150, 150), Size(60, 40), 0, 0, 360, CV_RGB(0, 0, 255));
    // 根据椭圆曲线找到其中点坐标
    vector<Point> ellipseVector;
    ellipse2Poly(Point(150, 150), Size(60, 40), 0, 0, 360, 100, ellipseVector);
    cout << ellipseVector << endl;  //[210, 150; 140, 189; 94, 136; 180, 115; 210, 150]
    // 画多边形
    cv::Point one_pts[5];
    one_pts[0] = cv::Point(400, 100);
    one_pts[1] = cv::Point(600, 200);
    one_pts[2] = cv::Point(500, 300);
    one_pts[3] = cv::Point(300, 300);
    one_pts[4] = cv::Point(200, 200);
    fillConvexPoly(backView, one_pts, 5, CV_RGB(0, 255, 0));

    cv::Point pts[1][5];
    pts[0][0] = cv::Point(500, 400);
    pts[0][1] = cv::Point(500, 500);
    pts[0][2] = cv::Point(600, 600);
    pts[0][3] = cv::Point(700, 500);
    pts[0][4] = cv::Point(600, 400);
    int npt[] = { 5 };
    const cv::Point *ppts[] = { pts[0] };
    fillPoly(backView, ppts, npt, 1, cv::Scalar(200, 200, 200));
    // 画线
    line(backView, Point(100, 400), Point(300, 800), CV_RGB(0, 123, 244));
    // 画矩形
    rectangle(backView, Point(400, 600), Point(600, 800), CV_RGB(231, 123, 244));
    // 画折线
    Point pp[1][5];
    pp[0][0] = cv::Point(500, 700);
    pp[0][1] = cv::Point(500, 800);
    pp[0][2] = cv::Point(600, 900);
    pp[0][3] = cv::Point(700, 800);
    pp[0][4] = cv::Point(600, 700);
    
    pp[1][0] = cv::Point(200, 200);
    pp[1][1] = cv::Point(400, 400);
    pp[1][2] = cv::Point(100, 200);
    int ppcount[] = { 5 };
    const Point* pps[1] = { pp[0], pp[1] };
    polylines(backView, pps, ppcount, 1, true, CV_RGB(32, 233, 12));
    // 文字
    putText(backView, "OpenCV", Point(700, 500), FONT_HERSHEY_COMPLEX, 2, CV_RGB(30, 12, 255));
    // 迭代器
    LineIterator l1 = LineIterator(backView, Point(900, 900), Point(backView.cols, backView.rows));
    vector<Vec3b> buf(l1.count);
    
    for (int i = 0; i < l1.count; i++, ++l1) {
//    for (Vec3b p : buf) {
//        ++l1;
        Point pt = l1.pos();
//        backView.at<Vec3b>(pt.y, pt.x) = 255;
        cout << backView.at<uchar>(pt.y, pt.x);
    }
    
    
    namedWindow("draw", WINDOW_NORMAL);
    resizeWindow("draw", Size(1000, 1000));
    moveWindow("draw", 500, 0);
    imshow("draw", backView);
    waitKey();
}

void example_6_2() {
    Mat img = imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    cvtColor(gray, gray, COLOR_GRAY2BGR);
    
    putText(gray, "Hello Apple", Point(100, 100), FONT_HERSHEY_PLAIN, 4, CV_RGB(255, 0, 0));
    imshow("6-2", gray);
    waitKey();
}

void example_6_3() {
    namedWindow("6-3");
    VideoCapture cap;
    cap.open("/Users/jw.hu/Desktop/OpenCV_Source/tree.avi");
    if (!cap.isOpened()) {
        cout << "读取视频失败" << endl;
        return;
    }
    
    int fps = cap.get(CAP_PROP_FPS);
    
    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        putText(frame, "FPS" + to_string(fps), Point(20, 20), 1, 1, CV_RGB(0, 0, 255));
        waitKey(1000 / fps);
        imshow("6-3", frame);
    }
    
    waitKey();
}



