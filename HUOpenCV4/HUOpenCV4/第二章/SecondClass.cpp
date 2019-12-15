//
//  SecondClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2019/12/13.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "SecondClass.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void showImage() {
    cv::Mat img = cv::imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    
    if (img.empty()) { return; }
    // 当直接使用 imshow 方法时 会自动运行 namedWindow 方法创建一个 window
//    cv::namedWindow("2-1", cv::WINDOW_OPENGL);
    cv::imshow("2-1", img);
    
    cv::waitKey(0);
    cv::destroyWindow("2-1");
    
}

void showVideo() {
    cv::namedWindow("2-2");
    cv::VideoCapture cap;
    cap.open("/Users/jw.hu/Desktop/OpenCV_Source/tree.avi");
    cv::Mat frame;
    for (;;) {
        cap >> frame;
        if (frame.empty()) { break; }
        
        cv::imshow("2-2", frame);
        if (cv::waitKey(33) >= 0) { break; }
    }
}

cv::VideoCapture g_cap;
int g_slider_position = 0;
int g_run = 1, g_dontset = 0;

void onTrackbarSlider(int pos, void *) {
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    
    if (!g_dontset) {
        g_run = 1;
    }
    g_dontset = 0;
}

void sliderVideo() {
    cv::namedWindow("2-3");
    g_cap.open("/Users/jw.hu/Desktop/OpenCV_Source/tree.avi");
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw   = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph   = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Video has " << frames << " frames of dimensions(" << tmpw << "," << tmph << ")." << endl;
    
    cv::createTrackbar("Position", "2-3", &g_slider_position, frames, onTrackbarSlider);
    
    cv::Mat frame;
    for (;;) {
        if (g_run != 0) {
            g_cap >> frame;
            if (frame.empty()) { break; }
            
            int current_pos = (int) g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            
            cv::setTrackbarPos("Position", "2-3", current_pos);
            cv::imshow("2-3", frame);
            g_run -= 1;
        }
        
        char c = (char) cv::waitKey(10);
        if (c == 's') {
            g_run = 1;
            cout << "single step, run = " << g_run << endl;
        } else if (c == 'r') {
            g_run = -1;
            cout << "Run mode, run = " << g_run << endl;
        } else if (c == 27) {
            break;
        }
        
        
    }
}
// 简单的变换
void exapmple2_5(const cv::Mat &image) {
    cv::namedWindow("2-4--in");
    cv::namedWindow("2-4--out");
    
    cv::imshow("2-4--out", image);
    
    cv::Mat out;
    cv::GaussianBlur(image, out, cv::Size(5, 5), 3, 3);
    cv::GaussianBlur(  out, out, cv::Size(5, 5), 3, 3);

    cv::imshow("2-5--out", out);
    
    cv::waitKey();
}
// 降采样
void pyr_test(const cv::Mat &image) {
    cv::imshow("origin", image);
    cv::Mat dest1 = cv::Mat(image.rows / 2, image.cols / 2, image.type());
    cv::pyrDown(image, dest1);
    cv::imshow("dest1", dest1);
    
    cv::Mat dest2 = cv::Mat(dest1.rows / 2, dest1.cols / 2, dest1.type());
    cv::pyrDown(dest1, dest2);
    cv::imshow("dest2", dest2);
    
    cv::waitKey();
}
// Canny 绘制
void canny_test(const cv::Mat &image) {
    cv::imshow("origin", image);
    
    cv::Mat dest;
    cv::Mat canny;
    cv::cvtColor(image, dest, cv::COLOR_BGR2GRAY);
    
    cv::Canny(dest, canny, 10, 100, 3, true);
    
    cv::imshow("dest", dest);
    cv::imshow("canny", canny);
    
    int x = 16, y = 32;
    cv::Vec3b intensity = image.at<cv::Vec3b>(y, x);
    
    uchar blue  = intensity[0];
    uchar green = intensity[1];
    uchar red   = intensity[2];
    
    cout << "At (x,y) = (" << x << "," << y << "): (blue, green, red) = (" << (unsigned int)blue << "," << (unsigned int) green << "," << (unsigned int)red << ")" << endl;
    cout << "Gray pixel there is: " << (unsigned int)dest.at<uchar>(x, y) << endl;
    
    cv::waitKey();
}

void camera_test() {
    cv::VideoCapture cap;
    cap.open(0);
    
    if (!cap.isOpened()) {
        cerr << "无法打开摄像头" <<endl;
    }
    cv::Mat frames;
    for (;;) {
        cap >> frames;
        if (frames.empty()) { break; }
        
        cv::imshow("camera", frames);
        if (cv::waitKey(33) >= 0) { break; }
    }
}
