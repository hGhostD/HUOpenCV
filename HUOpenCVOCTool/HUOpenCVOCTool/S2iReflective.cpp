//
//  S2iReflective.cpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2019/5/21.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "S2iReflective.hpp"

using namespace std;
using namespace cv;

int brightness_mat(const Mat &mat) {
    int sum = 0;
    int count = 1;
    int width = mat.cols;
    int height = mat.rows;
    for (int i = 0; i <  width; i++) {
        for (int j = 0; j < height; j++) {
            unsigned char a = (unsigned char)mat.at<char>(i,j);
            if (a != 0) {
                sum += a;
                count++;
            }
        }
    }
    return sum / count;
}

int calculate_mat_brightness(const Mat mat, vector<Point> points) {
    Mat mask, copyImg;
    mask = Mat::zeros(mat.size(), CV_8UC1);
    
    int width = mat.cols;
    int height = mat.rows;
    vector<vector<Point>> contour;
    contour.push_back(points);
    
    // 计算最小矩形的范围和给的点会有偏差，它会自己进行计算，
    // 会有位置偏移，如果识别范围在图片中心也许不会有问题，
    // 全图进行识别会出现崩溃
    Rect rect = minAreaRect(points).boundingRect();
    drawContours(mask, contour, 0, Scalar::all(255), -1);
    mat.copyTo(copyImg, mask);
    if (rect.x < 0) {
        rect.x = 0;
    }
    if (rect.y < 0) {
        rect.y = 0;
    }
    
    if (rect.x + rect.width > width) {
        rect.x = width - rect.width;
    }
    
    if (rect.y + rect.height > height) {
        rect.y = height - rect.height;
    }
    copyImg = copyImg(rect);
    return brightness_mat(copyImg);
}
// https://blog.csdn.net/dcrmg/article/details/53543341
void imageClarity() {
    Mat img = imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    Mat gray;
    
    cvtColor(img, gray, CV_BGR2GRAY);
    Mat sobel;
    Laplacian(gray, sobel, CV_16U);
    
    double meanValue = 0.0;
    meanValue = mean(sobel)[0];
    
    stringstream meanValueStream;
    string meanValueString;
    meanValueStream << meanValue;
    meanValueStream >> meanValueString;
    meanValueString = "Laplacvian Method" + meanValueString;
    putText(img, meanValueString, Point(20,50), CV_FONT_HERSHEY_COMPLEX, 0.8, Scalar(255,176,0));
    imshow("清晰度", img);
    waitKey();
    
}
