//
//  FourthClass.cpp
//  HUOpenCV4
//
//  Created by hu on 2019/12/18.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "FourthClass.hpp"
#include <opencv.hpp>
using namespace cv;
using namespace std;

void mat_test() {
    cv::Mat mat(300, 1000, 3.f, CV_32FC3);
    mat.setTo(cv::Scalar(127.f, 255.f, 0.f));
    cv::imshow("mat", mat);
    cv::waitKey();
}

void mat_copy() {
    cv::Mat apple = cv::imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    cv::Range range(100, 100);
    // Rect
    cv::Rect rect(10, 10, 200, 200);
    cv::Mat mat(apple, rect);
    cv::imshow("rect", mat);
    // Range
    cv::Range rangeRow(10, 210);
    cv::Range rangeCol(10, 210);
    cv::Mat matRange(apple, rangeRow, rangeCol);
    cv::imshow("range", matRange);
    
    cout << (int)apple.at<cv::Vec3b>(10, 10)[0] << endl;
    cout << apple.at<cv::Vec3b>(10, 10)[1] << endl;
    cout << (int)apple.at<cv::Vec3b>(10, 10)[2] << endl;

    cv::waitKey();

}

void example_4_1() {
    const int n_mat_size = 5;
    const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size};
    Mat n_mat( 3, n_mat_sz, CV_32FC1);
    
    cv::RNG rng;
    rng.fill(n_mat, cv::RNG::UNIFORM, 0.f, 1.f);
    
    const Mat* arrays[] = { &n_mat, 0 };
    Mat my_planes[1];
    NAryMatIterator it (arrays, my_planes);
}

void example_4_2() {
    const int n_mat_size = 5;
    const int n_mat_sz[] = {n_mat_size, n_mat_size, n_mat_size};
    cv::Mat n_mat0(3, n_mat_sz, CV_32FC1);
    cv::Mat n_mat1(3, n_mat_sz, CV_32FC1);
    
    
    cv::RNG rng;
    rng.fill(n_mat0, cv::RNG::UNIFORM, 0.f, 1.f);
    rng.fill(n_mat1, cv::RNG::UNIFORM, 0.f, 1.f);
    
    const cv::Mat* arrays[] = { &n_mat0, &n_mat1, 0};
    cv::Mat my_planes[2];
    cv::NAryMatIterator it(arrays, my_planes);
    
    float s = 0.f;
    int n = 0;
    for (int p = 0; p < it.nplanes; p++, ++it) {
        s += cv::sum(it.planes[0])[0];
        s += cv::sum(it.planes[1])[0];
        n++;
    }
}

void range_copy() {
    cv::Mat apple = cv::imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    apple.rowRange(0, 20);
    apple.colRange(0, 20);
    imshow("range", apple);
}

void test_4_a() {
    Mat mat = cv::Mat::zeros(500, 500, CV_8U);
    mat.setTo(Scalar(1.0f));
    
    imshow("mat", mat);
    while (1) {
        int key;
        key = waitKey(100);
        if (key == 27) {
            break;
        } else if (key > 47 && key < 58) {
            int value = key - 48;
            cout << value << endl;
        }
    }
}
