//
//  S2iImageTest.cpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2019/5/7.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "S2iImageTest.hpp"

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

void light(IplImage *image) {
    IplImage* gray = cvCreateImage(cvGetSize(image), image->depth, 1);
    if (image->nChannels == 3) {
        cvCvtColor(image, gray, CV_BGR2GRAY);
    }

    CvScalar scalar = cvAvg(gray);

    printf("图片亮度 %f", scalar.val[0]);
}

void drawROI(IplImage *image) {
    
}


IplImage* inpaint_mask = 0;
IplImage* img0 = 0, *img = 0, *inpainted = 0;
CvPoint prev_pt = {-1,-1};

void on_mouse( int event, int x, int y, int flags, void* zhang)
{
    if( !img )
        return;
    if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
        prev_pt = cvPoint(-1,-1);//初始化
    else if( event == CV_EVENT_LBUTTONDOWN )
        prev_pt = cvPoint(x,y);
    else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
    {//手一直在绘画
        CvPoint pt = cvPoint(x,y);
        if( prev_pt.x < 0 )
            prev_pt = pt;
        cvLine( inpaint_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
        cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
        prev_pt = pt;
        cvShowImage( "image", img );
    }
    if (event == CV_EVENT_RBUTTONUP) {
        cvFloodFill(inpaint_mask, cvPoint(x, y), cvScalarAll(255));
        IplImage*  segImage = cvCreateImage(cvGetSize(img), 8, 3);
        cvCopy(img, segImage, inpaint_mask);
        cvShowImage("water", segImage);
    }
}
void copyImg();
void s2iImageoperator() {
    copyImg();
//    img = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
//
//    cvNamedWindow("image");
//    inpainted = cvCloneImage(img);
//    inpaint_mask = cvCreateImage(cvGetSize(img), 8, 1);
//    cvZero(inpaint_mask);
//    cvZero(inpainted);
//    cvSetMouseCallback("image", on_mouse, 0);
//    cvRect(0, 0, 100, 200);
//    cvRectangle(img, cvPoint(0, 0), cvPoint(200, 200), cvScalarAll(255));
//
//    cvShowImage("image", img);
//    cvFloodFill(inpaint_mask, cvPoint(100, 100), cvScalarAll(255));
//
//    IplImage*  segImage = cvCreateImage(cvGetSize(img), 8, 3);
//    cvCopy(img, segImage, inpaint_mask);
//    cvShowImage("water", segImage);
    
//    cvWaitKey();
}

void draw() {
    img = cvLoadImage("/Users/jw.hu/Desktop/OpenCV_Source/smarties.png");
    Rect rect(10,20,100,50);
    
    CvMat image_roi = cvMat(100, 50, CV_8U);
    
    
    vector<vector<Point>> contour;
    vector<Point> pts;
    pts.push_back(Point(30,45));
    pts.push_back(Point(100,15));
    pts.push_back(Point(300,145));
    pts.push_back(Point(330,240));
    pts.push_back(Point(50,250));
    contour.push_back(pts);

    cvNamedWindow("s2i");
    cvShowImage("s2i", img);
    while (1) { if (cvWaitKey(15) == 27) { break; } }
    cvDestroyAllWindows();
}

void copyImg() {
    Mat image,mask;
    Rect r1(0, 0, 1000, 1000);
    Mat img1,img2,img3,img4;
    image = imread("/Users/jw.hu/Desktop/OpenCV_Source/apple.jpg");
    mask = Mat::zeros(image.size(), CV_8UC1);
//    mask(r1).setTo(255);
    
    vector<vector<Point>> contour;
    vector<Point> pts;
    pts.push_back(Point(30,45));
    pts.push_back(Point(100,15));
    pts.push_back(Point(300,145));
    pts.push_back(Point(330,240));
    pts.push_back(Point(50,250));
    contour.push_back(pts);
    
    
    
    Rect rr = minAreaRect(pts).boundingRect();
    cout << rr << endl;

    drawContours(mask, contour, 0, Scalar::all(255), -1);
    
//    img1 = image(rr);
    
    
    image.copyTo(img1, mask);
    img1 = img1(rr);


    Mat gray(rr.size(), CV_8U);
    
    cvtColor(img1, gray, CV_BGR2GRAY);
    
    long sum = 0;
    int count = 0;
    for (int i = 0; i < rr.br().x; i++) {
        for (int j = 0; j < rr.br().y; j++) {
            unsigned char a = (unsigned char)img1.at<char>(i,j);
            if (a != 0) {
                sum += a;
                count++;
            }
//            cout << (int)a << " ";
//            int value = a + 255;
//            if (value != 255) {
//                sum += value;
//                count++;
//            }
        }
    }
    
    cout << "sum:" << sum << "\ncount:" << count << "\nresult:" << sum / count << endl;
    

    image.copyTo(img2, mask);
//
//    image.copyTo(img3);
//    img3.setTo(0, mask);
//
//    imshow("ImageSequence", image);
    imshow("img1", gray);
    imshow("img2", img2);
//    imshow("img3", img3);
//    imshow("mask", mask);
    
    IplImage ii = img1;
    IplImage *ii1 = &ii;
    
    IplImage i2 = img2;
    IplImage *ii2 = &i2;
    
    IplImage i3 = img3;
    IplImage *ii3 = &i3;
    light(ii1);
    light(ii2);
//    light(ii3);
    
    waitKey();
}
