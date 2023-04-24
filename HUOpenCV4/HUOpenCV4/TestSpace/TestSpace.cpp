//
//  TestSpace.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/3/28.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "TestSpace.hpp"
#include <opencv.hpp>

using namespace cv;
using namespace std;

void detect_sharpness() {
    
    Mat img = imread("/Users/hujiawen/Desktop/小程序测试图片/1.jpeg");
    Mat dst, lap;
    
    Scalar mu,stddev;
    
    cvtColor(img, dst, COLOR_RGB2GRAY);
    
    Laplacian(dst, lap, CV_64F);
    meanStdDev(lap, mu, stddev);
    
    int r;
    r = stddev.val[0];
    
    cout << r * r << endl;
//    cout << (int)stddev.val[0] << endl;
    
}

void createAlphaMat(Mat & mat) {
    for (int row = 0; row < mat.rows; row++) {
        for (int col = 0; col < mat.cols; col++) {
            Vec4b & rgba = mat.at<Vec4b>(row, col);
            
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar>(float(mat.cols - col) / (float)(mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>(float(mat.rows - row) / (float)(mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}

void test_alphat() {
    
    Mat mat(480, 640, CV_8UC4);
    createAlphaMat(mat);
    
    vector<int>compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    
    imwrite("/Users/hujiawen/Desktop/透明.png", mat, compression_params);
    
    imshow("PNG 图片", mat);
    waitKey(3000);
}

void test_addWeight()
{
    
    Mat img = imread("/Users/hujiawen/Pictures/shenhe.jpeg" );
    Mat logo = imread("/Users/hujiawen/Downloads/IMG_2459.JPG");
    // 创建 img 的感应区域, 区域位置自定, 大小与 logo 相同, 针对此区域操作就会影响 img
    Mat imgROI;
    imgROI = img(Rect(img.cols - logo.cols, img.rows - logo.rows, logo.cols, logo.rows));
//    addWeighted(imgROI, 0.5, logo, 0.3, 0., imgROI);
    for(int row = 0; row < logo.rows; ++row) {
        imgROI.row(row) = Vec3b(255, 255, 255);
//        for(int col = 0; col < logo.cols; ++col) {
//            Vec3b & rgb = imgROI.at<Vec3b>(row, col);
//            rgb[0] = 255;
//            rgb[1] = 255;
//            rgb[2] = 255;
//        }
    }
    
    imshow("shenhe + logo", img);
//    imwrite("/Users/hujiawen/Desktop/logo.jpg", img);
    waitKey(3000);
}

void test_format() {
//    Mat img = imread("/Users/hujiawen/Desktop/lenna.jpg");
//    cout << format(img, cv::Formatter::FMT_C);
    Vec3b v(1,2,3);
    cout << format(Mat(v), cv::Formatter::FMT_PYTHON);
    
//    printf("%s", format(v, cv::Formatter::FMT_PYTHON));
}

void track_callback(int pos, void* userdata) {
    int p = getTrackbarPos("滑动条名字", "img");
    printf("\n %d %d", pos, p);
    Mat img = imread("/Users/hujiawen/Desktop/lenna.jpg");
    Size size(pos + 1, pos + 1);
    blur(img, img, size);
    imshow("img", img);
}

void test_track() {
    /**
        创建滚动条联系
        1. 创建一个图片
        2. 图片底部放置一个等宽滚动条
        3.滑动滚动条可以改变图片模糊程度 范围从 0 ~ 100
     */
    
    namedWindow("img");
   
    int blur_value = 0;
    int *v = &blur_value;
    
    createTrackbar("TrackName", "img", v, 100, track_callback);
    track_callback(*v, 0);
    if (waitKey() == 27) {
        return;
    }
    
}


bool isDraw;
Point p1, p2;
void mouse_callback(int event, int x, int y, int flags, void* userdata) {
//    printf("\n %d %d %d %d", event, x, y, flags);
    Mat & mat = *(Mat *)userdata;
    
    switch (event) {
        case EVENT_LBUTTONDOWN:
            p1.x = x;
            p1.y = y;
            isDraw = true;
            break;
            
        case EVENT_LBUTTONUP:
            p2.x = x;
            p2.y = y;
            isDraw = false;
            break;
        default:
            break;
    }
    
//    Mat img;
    if (isDraw) {
        rectangle(mat, p1, p2, Scalar(0, 0, 255));
        p1 = Point();
        p2 = Point();
    }
    imshow("img", mat);
}

void test_mousecallback() {
    /**
    创建黑色背景图  1000 * 1000
     创建鼠标操作
     1. 点下左键
     2. 移动鼠标
     3.松开鼠标
     */
    Mat img(1000, 1000, CV_8UC3);
    imshow("img", img);
    
    void *mat_h = &img;
    setMouseCallback("img", mouse_callback, mat_h);
    waitKey();
}

void test_books() {
    double t = (double)getTickCount();
    // do something ...
    
    Mat img = imread("/Users/hujiawen/Desktop/lenna.jpg");
    
    t = ((double)getTickCount() - t)/getTickFrequency();
    printf("\n %f", t);
}
