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
    mask = Mat::zeros(mat.size(), CV_8U);
    
    
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

bool isCntValid(vector<Point> cnt, int rows, int cols) {
    for (Point point : cnt) {
        if (point.x == 0 || point.y == 0 || point.x == rows - 1 || point.y == cols - 1) {
            return false;
        }
    }
    return true;
}
// 计算两点之间的距离
double distanceOfPoint(Point p1, Point p2) {
    double x = abs(p1.x - p2.x);
    double y = abs(p1.y - p2.y);
    return sqrt(pow(x, 2) + pow(y, 2));
}

bool isCntScaleValid(vector<Point> cnt) {
    if (cnt.size() == 4) {
        Point p0 = cnt[0];
        Point p1 = cnt[1];
        Point p2 = cnt[2];
        double width = floor(distanceOfPoint(p0, p1));
        double height = floor(distanceOfPoint(p1, p2));
        double scale = width / height;
        if (scale > 0.7 && scale < 1.4) {
            return true;
        }
    }
    return false;
}

double angleOfPoint(Point pt1, Point pt2, Point pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}
void traverse_points_find_square(const Mat gray, vector<vector<Point> > contours, vector<vector<Point> > &squares) {
    // 找到形状的边缘轮廓点
    findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    vector<Point> approx;
    for (vector<Point> points : contours) {
        approxPolyDP(points, approx, arcLength(points, true) * 0.02, true);
        if (approx.size() == 4 &&
            fabs(contourArea(approx)) > 1000 &&
            isContourConvex(approx) &&
            isCntValid(approx, gray.rows, gray.cols) &&
            // 判断
            isCntScaleValid(approx)) {
            double maxCosine = 0;

            for (int j = 2; j < 5; j++) {
                double angle = angleOfPoint(approx[j%4], approx[j-2], approx[j-1]);
                double cosine = fabs(angle);
                maxCosine = MAX(maxCosine, cosine);
            }
            // 判断两个边的夹角接近90度垂直
            if (maxCosine < 0.3) {
                // 计算面积最大的四边形
                squares.push_back(approx);
            }
        }
    }
}

vector<vector<Point>> detect_square(const Mat mat, const int gauss_filter_size = 15) {
    vector<vector<Point> > squares;
    Mat destination, gray;

    vector<vector<Point> > contours;

    // 2. Gauss模糊处理
    GaussianBlur(mat, destination, Size(gauss_filter_size, gauss_filter_size), 0);
    //    imwrite("/Users/jw.hu/Desktop", destination);
    imshow("blur", destination);
    // 3. 通过canny找边线，或者黑白阈值
    for (int l = 0; l < 255; l += 5) {
        if (l == 0) {
            Canny(destination, gray, 0, 50, 7);
            imshow("canny", gray);
            dilate(gray, gray, Mat());
        } else {
            threshold(destination, gray, l, 255, THRESH_BINARY);
        }

        // 找到形状的边缘轮廓点
        traverse_points_find_square(gray, contours, squares);
    }
    return squares;
}
void imageOperator() {
    Mat img = imread("/Users/mac/Desktop/OpenCV_Source/pic3.png");
    imshow("source", img);
    
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);
    imshow("gray", gray);
    
    vector<vector<cv::Point>> pointArray = detect_square(gray);
    drawContours(img, pointArray, 50, Scalar(0, 255, 0));
    imshow("draw", img);
    // 轮廓
//    Mat canny;
//    Canny(gray, canny, 200, 500);
//    imshow("canny", canny);
    
    waitKey();
}

