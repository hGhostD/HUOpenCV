//
//  S2iImageTest.cpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2019/5/7.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "S2iImageTest.hpp"

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

bool isCntValid(vector<Point> cnt, int rows, int cols) {
    for (auto point : cnt) {
        if (point.x == 0 || point.y == 0 || point.x == rows - 1 || point.y == cols - 1) {
            return false;
        }
    }
    return true;
}

bool isCntScaleValid(vector<Point> cnt) {
    if (cnt.size() == 4) {
        Point p0 = cnt[0];
        Point p2 = cnt[2];
        double width = abs(p0.x - p2.x);
        double height = abs(p0.y - p2.y);
        double scale = width / height;
        if (scale > 0.8 && scale > 1.4) {
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

Mat findSquares(Mat image, vector<vector<Point>> &squares) {
    Mat mat, destination, gray, result;
    
    squares.clear();
    vector<vector<Point>> contours;
    GaussianBlur(mat, destination, Size(15, 15), 0);
    cvtColor(mat, result, COLOR_GRAY2RGB);
    
    for (int l = 0; l < 255; l += 26) {
        if (l == 0) {
            Canny(destination, gray, 0, 5);
            dilate(gray, gray, Mat());
        } else {
            threshold(destination, gray, l, 255, THRESH_BINARY);
        }
        
        findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
        
        vector<Point> approx;
        for (vector<Point> points : contours) {
            approxPolyDP(points, approx, arcLength(points, true) * 0.02, true);
            if (approx.size() == 4 &&
                fabs(contourArea(approx)) > 1000 &&
                isContourConvex(approx)) {
                
                if (isCntValid(approx, destination.rows, destination.cols) &&
                    isCntScaleValid(approx)) {
                    double maxCosine = 0;
                    
                    for (int j = 2; j < 5; j++) {
                        double angle = angleOfPoint(approx[j%4], approx[j-2], approx[j-1]);
                        double cosine = fabs(angle);
                        maxCosine = MAX(maxCosine, cosine);
                    }
                    if (maxCosine < 0.1) {
                        line(result, approx[0], approx[1], Scalar(255, 0, 0), 10);
                        line(result, approx[1], approx[2], Scalar(255, 0, 0), 10);
                        line(result, approx[2], approx[3], Scalar(255, 0, 0), 10);
                        line(result, approx[3], approx[0], Scalar(255, 0, 0), 10);
                        squares.push_back(approx);
                    }
                }
            }
        }
    }
    return result;
}
