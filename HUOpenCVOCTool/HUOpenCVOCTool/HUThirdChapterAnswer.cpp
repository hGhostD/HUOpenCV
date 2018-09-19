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

void third_first() {
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
void third_second() {
    CvMat* mat = cvCreateMat(width, height, CV_8UC3);
    cvSetZero(mat);

    //a 使用 cvCircle 方法画一个圆
    cvCircle(mat, cvPoint(width / 2, height / 2), width / 4, CvScalar(255, 176, 0));

    //b 使用第二章的方法来显示这幅图
    show("2", mat);
}
// 3.通过 cvPtr2D 将指针指向中间的通道("绿色").以(20,5)与(40,20)为定点画一个绿色长方形.
// 4.画一个绿色平面
void third_third(bool isFillColor) {
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
void third_fifth() {
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
// 为一个图像创建多个图像头。
void third_sixth(const char* fileName) {
    IplImage* image = cvLoadImage(fileName);
    IplImage* header1 = cvCreateImageHeader(cvSize(20, 30), image->depth, image->nChannels);
    IplImage* header2 = cvCreateImageHeader(cvSize(20, 30), image->depth, image->nChannels);
    header1->origin = image->origin;
    header2->origin = image->origin;
    header1->widthStep = image->widthStep;
    header2->widthStep = image->widthStep;
    
    header1->imageData = image->imageData + 10 * image->widthStep + 5 * image->nChannels;
    header2->imageData = image->imageData + 60 * image->widthStep + 50 * image->nChannels;
    
    cvNot(header1, header1);
    cvNot(header2, header2);
    
    show("6", image);
    cvReleaseImageHeader(&header1);
    cvReleaseImageHeader(&header2);
}
// 使用 cvCmp() 创建一个掩码。加载一个真实的图形。使用 cvSplit() 将图像分割成红，绿，蓝三个单通道图像。
void third_seventh(const char* fileName) {
    IplImage* image = cvLoadImage(fileName);
    CvSize size = cvSize(image->width, image->height);
    IplImage* image_b = cvCreateImage(size, image->depth, 1);
    IplImage* image_g = cvCreateImage(size, image->depth, 1);
    IplImage* image_r = cvCreateImage(size, image->depth, 1);
    // a 找到并显示绿色
    cvSplit(image, image_b, image_g, image_r, NULL);
//    show("7-a", image_g);
    // b 克隆这个绿色图两次(分辨命名为 clone1 和 clone2)
    IplImage* clone1 = cvCloneImage(image_g);
    IplImage* clone2 = cvCloneImage(image_g);
    // c 求出这个绿色平面的最大值和最小值
    double min, max;
    cvMinMaxLoc(image_g, &min, &max);
    printf("min:%f, max:%f", min, max);
    // d 将 clone1 的所有元素赋值为 thresh=(unsigned char)((最大值 - 最小值)/2.0)
    unsigned char thresh = (max - min) / 2.0;
    // e 将 clone2 的所有元素赋值为 0,然后调用函数 cvCmp()
    cvSet(clone1, cvScalar(thresh));
    cvSetZero(clone2);
    cvCmp(image_g, clone1, clone2, CV_CMP_GE);
    // f 使用 cvSubS 函数并显示结果
    cvSubS(image_g, thresh / 2, image_g, clone2);
    show("7-f", image_g);
}
// 创建一个结构，结构中包含一个整数，一个 CvPoint 和一个 CvRect；称结构为 "my_struct"
// a 写两个函数：void write_my_struct(CvFileStorage * fs, const char* name, my_struct* ms)和void read_my_struct(CvFileStorage* fs, CvFileNode* ms_node, my_struct* ms
struct my_struct {
    int index;
    CvPoint point;
    CvRect rect;
};
void write_my_struct(CvFileStorage * fs, const char* name, my_struct* ms) {
    cvStartWriteStruct(fs, name, CV_NODE_MAP);
    // 写入 int
    cvStartWriteStruct(fs, "index", CV_NODE_SEQ);
    cvWriteInt(fs, NULL, ms->index);
    cvEndWriteStruct(fs);
    // 写入 CvPoint
    cvStartWriteStruct(fs, "CvPoint", CV_NODE_SEQ);
    cvWriteInt(fs, NULL, ms->point.x);
    cvWriteInt(fs, NULL, ms->point.y);
    cvEndWriteStruct(fs);
    // 写入 CvRect
    cvStartWriteStruct(fs, "CvRect", CV_NODE_SEQ);
    cvWriteInt(fs, NULL, ms->rect.x);
    cvWriteInt(fs, NULL, ms->rect.y);
    cvWriteInt(fs, NULL, ms->rect.width);
    cvWriteInt(fs, NULL, ms->rect.height);
    cvEndWriteStruct(fs);
    cvEndWriteStruct(fs);
}
void read_my_struct(CvFileStorage* fs, CvFileNode* ms_node, my_struct* ms) {
    // 读取 index
    CvSeq* i = cvGetFileNodeByName(fs, ms_node, "index")->data.seq;
    ms-> index = cvReadInt((CvFileNode *)cvGetSeqElem(i, 0));

    // 读取 point
    CvSeq* s1 = cvGetFileNodeByName(fs, ms_node, "CvPoint")->data.seq;
    CvPoint point;
    point.x = cvReadInt((CvFileNode *)cvGetSeqElem(s1, 0));
    point.y = cvReadInt((CvFileNode *)cvGetSeqElem(s1, 1));
    ms->point = point;
    
    // 读取 rect
    CvSeq* s2 = cvGetFileNodeByName(fs, ms_node, "CvRect")->data.seq;
    CvRect rect;
    rect.x = cvReadInt((CvFileNode *)cvGetSeqElem(s2, 0));
    rect.y = cvReadInt((CvFileNode *)cvGetSeqElem(s2, 1));
    rect.width = cvReadInt((CvFileNode *)cvGetSeqElem(s2, 2));
    rect.height = cvReadInt((CvFileNode *)cvGetSeqElem(s2, 3));
    ms->rect = rect;
    
}
// 将MyStruct的值显示出来
void ShowStructValue(my_struct* pvalue) {
    printf("integer:%d\n", pvalue->index);
    printf("CvPoint: (%d, %d)\n", pvalue->point.x, pvalue->point.y );
    printf("CvRect: h-->%d\tw-->%d\t(%d, %d)\n", pvalue->rect.height,
           pvalue->rect.width, pvalue->rect.x, pvalue->rect.y);
}
// 检查两个MyStruct是否一致
bool check(my_struct* msValue1, my_struct* msValue2) {
    if((msValue1->index == msValue2->index) &&
       (msValue1->point.x == msValue2->point.x) &&
       (msValue1->point.y == msValue2->point.y) &&
       (msValue1->rect.height == msValue2->rect.height) &&
       (msValue1->rect.width == msValue2->rect.width) &&
       (msValue1->rect.x == msValue2->rect.x) &&
       (msValue1->rect.y == msValue2->rect.y))
        return true;
    else
        return false;
}

void third_eighth(const char* fileName) {
    
    // 写入部分
    my_struct msArray[10];
    CvFileStorage* fs = cvOpenFileStorage(fileName, 0, CV_STORAGE_WRITE);
    char pchTag[12];
    // 生成随机数据
    for (int i = 0; i < 10; i++) {
        CvRNG rng = cvRNG(cvGetTickCount());

        msArray[i].index = cvRandInt(&rng) % 256;
        msArray[i].point = cvPoint(cvRandInt(&rng) % 1000, cvRandInt(&rng) % 1000);
        msArray[i].rect = cvRect(cvRandInt(&rng) % 1000, cvRandInt(&rng) % 1000, cvRandInt(&rng) % 600, cvRandInt(&rng) % 600);

        sprintf(pchTag, "my_struct_%d", i);
        write_my_struct(fs, pchTag, &msArray[i]);
    }
    cvReleaseFileStorage(&fs);
    
    // 读取部分
    fs = cvOpenFileStorage(fileName, NULL, CV_STORAGE_READ);
    my_struct msArrayRead[10];
    CvFileNode* pnode;
    
    for (int i = 0; i < 10; i++) {
        sprintf(pchTag, "my_struct_%d", i);
        pnode = cvGetFileNodeByName(fs, NULL, pchTag);
        read_my_struct(fs, pnode, &msArrayRead[i]);
        // 显示
        printf("---------------------- %d: Write -------------------------\n", i);
        ShowStructValue(&msArray[i]);
        printf("---------------------- %d: Read --------------------------\n", i);
        ShowStructValue(&msArrayRead[i]);
        // 检查读写是否一致
        if(check(&msArray[i], &msArrayRead[i] )) {
            printf("Consistent?:\tAnswer: True\n");
        } else {
            printf("Consistent?:\tAnswer: False\n");
        }
        getchar();

    }
    cvReleaseFileStorage(&fs);
}
