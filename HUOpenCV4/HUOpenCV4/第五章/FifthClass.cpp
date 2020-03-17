//
//  FifthClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2020/1/20.
//  Copyright © 2020 jw.hu. All rights reserved.
//

#include "FifthClass.hpp"
#include <opencv.hpp>
using namespace cv;
using namespace std;
/*
 
 abs()                  计算矩阵中所有元素的绝对值
 adbsdiff()             计算两个居中差值的绝对值
 add()                  实现两个矩阵逐元素相加
 addWeighted()          实现两个矩阵逐元素加权求和(以为混合值)
 bitwise_and()          计算两个矩阵逐元素按位与
 bitwise_not()          按位非
 bitwise_or()           计算两个矩阵逐元素按位或
 bitwise_xor()          计算两个矩阵逐元素按位异或
 calcCovarMatrix()      计算一组n维向量的协方差
 cartToPolar()          计算二维向量的角度和幅度
 checkRange()
 completeSymm()
 convertScaleAbs()

 */
void learn_abs() {

    Mat a = Mat::ones(2, 2, CV_32FC1);
    Mat b = Mat(2, 2, CV_32FC1, Scalar(-5));

    Mat c = abs(b);
    cout << c << endl;

    absdiff(b, a, c);

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
  
}
// https://blog.csdn.net/huqiaolong/article/details/96354503
void example_5_1_a() {
    Mat orign = Mat::zeros(100, 100, CV_32FC3);
    cv::circle(orign, Point(50, 50), 50, Scalar(0, 0, 255));
    imshow("5-1", orign);
    waitKey();
}

void example_5_2() {
    Mat orign = Mat::zeros(100, 100, CV_32FC3);
    // -1 代表填充颜色
    cv::rectangle(orign, Point(20, 5), Point(40, 20), Scalar(0, 255, 0), -1);
    imshow("5-2", orign);
    waitKey();
}

void example_5_4() {
    Mat m(210, 210, CV_8UC1);
 
    for (int i = 1; i < 11; i++) {
        Rect rest(10 * i, 10 * i, 210 - 20 * i, 210 - 20 * i);//定义一个框
        Mat tmp = m(rest);//这个tmp是个引用
        tmp.setTo((i + 1) * 20);//setTo能进行值的设置
    }
    
    imshow("5-4", m);
    waitKey();
}

void example_5_5() {
    Mat img = imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    
    Rect r1(5, 10, 20, 30);
    Rect r2(50, 60, 20, 30);
    
    Mat m1 = img(r1);
    Mat m2 = img(r2);
    
    cv::bitwise_not(m1, m1);
    cv::bitwise_not(m2, m2);
    
    imshow("5-5", img);
    waitKey();
}

void example_5_6() {
    Mat img = imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    
    vector<Mat> b_g_r;
    
    split(img, b_g_r);
    
    imshow("input", img);
    // a
    imshow("output", b_g_r[1]);
    // b
    Mat clone1 = b_g_r[1].clone();
    Mat clone2 = b_g_r[2].clone();
    // c
    double min, max;
    minMaxLoc(clone1, &min, &max);
    
    cout << "min :" << min << endl;
    cout << "max :" << max << endl;
    // d
    uchar thresh = (uchar)(max - min) / 2;
    clone1 = thresh;
    imshow("clone1", clone1);
    // e
/*
 enum {
     CMP_EQ=0,    //相等
     CMP_GT=1,   //大于
     CMP_GE=2,   //大于等于
     CMP_LT=3,   //小于
     CMP_LE=4,   //小于等于
     CMP_NE=5 }; //不相等
 
 compare(InputArray src1, InputArray src2, OutputArray dst, int cmpop);
 用途举例：

 这个函数有一个很有用的地方就是：当你需要从一幅图像中找出那些特定像素值的像素时，可以用这个函数。类似与threshold()函数，但是threshold()函数是对某个区间内的像素值进行操作，compare()函数则可以只是对某一个单独的像素值进行操作。比如我们要从图像中找出像素值为50的像素点，可以下面这样做：

        cv::Mat result;
        cv::compare(image,50, result, cv::CMP_EQ);
 */
    clone2 = 0;
    compare(b_g_r[1], clone1, clone2, cv::CMP_GE);      // 这样做就将大于等于平均值的像素点过滤掉
    imshow("clone2", clone2);

    // f
    subtract(b_g_r[1], thresh/ 2, b_g_r[1], clone2);
    imshow("subtract", b_g_r[1]);
    
    waitKey();
}
