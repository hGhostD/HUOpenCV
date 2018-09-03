//
//  HUThirdChapterAnswer.cpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2018/9/3.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#include "HUThirdChapterAnswer.hpp"
#include <opencv/cxcore.hpp>
#include <opencv/highgui.h>


void show(const char* fileName, const CvArr *image) {
    cvShowImage(fileName, image);
    cvWaitKey();
    cvReleaseData(&image);
    cvDestroyAllWindows();
}
/*
 书后第三章习题
 */

void first() {
    float pi = -3.1415926;
    //a 选取一个负的浮点数, 取它的绝对值,四舍五入后,取它的极值
    float abs_pi = CV_IABS(pi);
    int round_pi = cvRound(abs_pi);
    printf("绝对值:%lf, 极值:%i \n", abs_pi, round_pi);
    //b 产生一个随机数
    CvRNG rng = cvRNG(cvGetTickCount());
    printf("随机数 int:%i, 随机数 float:%lf \n", cvRandInt(&rng) % RAND_MAX, cvRandReal(&rng));
    //c 创建一个浮点型 cvPoint2D32f, 并转化成一个整数型 cvPoint
    CvPoint2D32f point_2d32f = cvPoint2D32f(2.5, 3.5);
    CvPoint point = cvPointFrom32f(point_2d32f);
    printf("cvPoint:%u, %u \n", point.x, point.y);
    //d 将一个 cvPoint 转化成一个 cvPoint2D32f
    CvPoint2D32f new_point = cvPointTo32f(point);
    printf("cvPoint2D32f:%f, %f\n", new_point.x, new_point.y);
}

int width = 1000;
int height = 1000;
// 创造一个三通道二位矩阵,字节类型,大小为 100*100, 并设置所有数值为0
void second() {
    CvMat* mat = cvCreateMat(width, height, CV_8UC3);
    cvSetZero(mat);

    //a 使用 cvCircle 方法画一个圆
    cvCircle(mat, cvPoint(width / 2, height / 2), width / 4, CvScalar(255, 176, 0));

    //b 使用第二章的方法来显示这幅图
    show("2", mat);
}
// 3.通过 cvPtr2D 将指针指向中间的通道("绿色").以(20,5)与(40,20)为定点画一个绿色长方形.
// 4.画一个绿色平面
void third(bool isFillColor) {
    CvMat* mat = cvCreateMat(100, 100, CV_8UC3);
    cvSetZero(mat);
    if (!isFillColor) {
        int left = 20,top=5,right=40,bottom = 20;
        for( ;left<=right;left++) {
            *(cvPtr2D(mat,left,top,NULL)+1)=255;
            *(cvPtr2D(mat,left,bottom,NULL)+1)=255;
        }
        left = 20;
        for( ;top<=bottom;top++) {
            *(cvPtr2D(mat,left,top,NULL)+1)=255;
            *(cvPtr2D(mat,right,top,NULL)+1)=255;
        }
    }else {
        for (int i = 0; i < mat->cols; i++) {
            for (int j = 0; j < mat->rows; j++) {
                if (i < 20 && i < 40 && j > 5 && j < 20)
                    *(cvPtr2D(mat, i, j) + 1) = 255;
            }
        }
    }
    show("3", mat);
}
// 使用 ROI 和 cvSet() 建立一个增长如金字塔状的数组
void fifth() {
    IplImage* image = cvCreateImage(cvSize(210, 210), 8, 1);
    cvSetZero(image);
    
    int value = 0;
    int rect_size = 210;
    for (int length = rect_size; length >= 0 && value <= 100; length -= 10, value += 10) {
        cvSetImageROI(image, cvRect(210 - length, 210 - length, rect_size, rect_size));
        rect_size -= 2 * 10;
        cvSet(image, cvScalarAll(value));
        cvResetImageROI(image);
    }
    show("4", image);
}
