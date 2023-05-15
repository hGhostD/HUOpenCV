//
//  Eleventh.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/4/6.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "Eleventh.hpp"

void resizeCompare() {
    Mat lenna = imread("/Users/hujiawen/Desktop/lenna.jpg");
    Mat r2;
    resize(lenna, r2, Size(), 0.1, 0.1);
    lenna.resize(100, Scalar(0,0,0));
//    lenna.resize(s);
//    Mat r3 = cv::Mat::resize(s);
    imshow("r1", lenna);
    imshow("r2", r2);
//    imshow("r3", r3);
    
    if (waitKey() == 27) {
        return;
    };
}

void showHist() {
    Mat lenna = imread("/Users/hujiawen/Desktop/lenna.jpg", IMREAD_GRAYSCALE);
    Mat dst;
    Mat hough = lenna.clone();
//    equalizeHist(lenna, dst);
//    imshow("Hist", dst);
    
    vector<Vec3f> circles;
    HoughCircles(lenna, circles, HOUGH_GRADIENT, 200, lenna.cols / 10);
    
    for (auto c : circles){
        cout << c << endl;
        circle(hough, Point2f(c[0], c[1]), c[2], Scalar(0,0,255), 10);
    }
    
//    imshow("Hough", hough);
//    waitKey();
    
    Mat doubleLenna(lenna.rows, lenna.cols * 2, CV_8U);
    for (int row = 0; row < lenna.rows; row++) {
        for (int col = 0; col < lenna.cols; col++) {
            doubleLenna.at<uchar>(row, col) = lenna.at<uchar>(row, col);
            doubleLenna.at<uchar>(row, col + lenna.cols) = lenna.at<uchar>(row, col);
        }
    }
    
    imshow("double", doubleLenna);
    waitKey();
    
}

void copy_img_split() {
    Mat lenna = imread("/Users/hujiawen/Desktop/lenna.jpg");
    Mat dst(lenna.size(), lenna.type());
    
    Rect r1(0, 0, lenna.cols, lenna.rows / 2);
    Mat d = lenna(r1);
    Rect r2(0, lenna.rows / 2, lenna.cols, lenna.rows / 2);
    Mat r = dst(r2);
    Mat z = dst(r1);
    d.copyTo(z);
    d.copyTo(r);
    
    imshow("split", dst);
    waitKey();

}

void test_warpPerspective() {
    Mat lenna = imread("/Users/hujiawen/Desktop/lenna.jpg");
    
    Mat transform;
    Point2f p11(0, 0);
    Point2f p12(100, 0);
    Point2f p13(100, 100);
    Point2f p14(0, 1000);
    Point2f p1[4] = {p11, p12, p13, p14};
    Point2f p2[4] = {Point2f(10, 10), Point2f(20, 30), Point2f(80, 80), Point2f(0,90)};
    
    transform = getPerspectiveTransform(p1, p2);
    
    warpPerspective(lenna, lenna, transform, lenna.size());
    imshow("lenna", lenna);
    waitKey();

}

