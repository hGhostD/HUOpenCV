//
//  TestSpace.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/3/28.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "TestSpace.hpp"
#include <opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

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

void test_iterator() {
    double t = (double)getTickCount();
    // do something ...
    
    Mat img = imread("/Users/hujiawen/Desktop/lenna.jpg");
    
    t = ((double)getTickCount() - t)/getTickFrequency();
    printf("\n %f", t);
    
    
    Mat_<Vec3b>::iterator it = img.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = img.end<Vec3b>();
    
    for(; it != itend; ++it) {
        printf("%d ", (*it)[0]);
    }
}

void test_copyTo() {
    Mat img = imread("/Users/hujiawen/Desktop/lenna.jpg");
    Mat logo = imread("/Users/hujiawen/Downloads/nike.png", IMREAD_UNCHANGED);
    double scale = (double)logo.cols / (double)logo.rows;
    
    int width = 200;
    int height = 200 / scale;
    Rect rect(img.cols - 100 - width, 100, width, height);
    cv::resize(logo, logo, rect.size());
    
    Mat alpha;
    
    vector<Mat> channels;
    split(logo, channels);
    alpha = channels[3];
//    threshold(alpha, alpha, 127, 255, THRESH_BINARY);
    double t = (double)getTickCount();

//    for(int row = 0; row < alpha.rows; ++row) {
//        for(int col = 0; col < alpha.cols; ++col) {
//            uchar & c = alpha.at<uchar>(row, col);
//            if (c > 125) {
//                c = 0;
//            } else {
//                c = 255;
//            }
//        }
//    }
//    Mat_<uchar>::iterator it = alpha.begin<uchar>();
//    Mat_<uchar>::iterator end = alpha.end<uchar>();
//    for (; it != end; ++it) {
//        uchar pt = *it;
//        if (pt > 125) {
//            pt = 0;
//        } else {
//            pt = 255;
//        }
//        *it = pt;
//    }
//
//    uchar *p = alpha.data;
//    for (int i = 0; i < alpha.total(); ++i) {
//        uchar *v = &p[i];
//        if (*v > 125) {
//            *v = 0;
//        } else {
//            *v = 255;
//        }
//        p[i] = *v;
//    }
    t = ((double)getTickCount() - t);
    std::cout << "time:" << t << std::endl;
    /**
     使用 Mask 进行图片加载
     1. 原始图片设置 ROI 区域
     2. logo 图片 变换为 ROI 区域同样尺寸
     3. logo 图片 copyTo 到 ROI 区域
     */
    
    std::cout << rect << std::endl;
    Mat roi = img(rect);
    cvtColor(alpha, alpha, COLOR_GRAY2BGR);
//    alpha.copyTo(roi);
    Mat temp;
    alpha.copyTo(roi, alpha);
//    roi.copyTo(temp, alpha);
//    temp.copyTo(roi);
//    roi = temp;
//    addWeighted(img, 0.5, imgCopy, 0.5, 0, img);
    imshow("roi", img);
    waitKey(3000);
    
}

void test_books() {
    
    test_copyTo();
    return;
    
    Mat img = imread("/Users/hujiawen/Desktop/lenna.jpg");
    Mat logo = imread("/Users/hujiawen/Downloads/nike.png", IMREAD_UNCHANGED);
    Mat roi = img(Rect(100, 100, 200, 100));
    cv::resize(logo, logo, Size(200, 100));
    Mat alpha;
    
    vector<Mat> channels;
    split(logo, channels);
    alpha = channels[3];
    Mat mask = Mat::zeros(100, 200, CV_8UC1);
    circle(mask, Point(50, 50), 50, Scalar(255), -1);
//    Mat l = roi.clone();
    Mat dst = Mat::zeros(roi.size(), roi.type());
    roi.copyTo(dst, alpha);
    roi = dst;
    imshow("logo", roi);
    waitKey(3000);
}

namespace mao_book {
void findConvexHull() {
    
    Mat img(600, 600, CV_8UC3);
    RNG &rng = theRNG();
    
    while (1) {
        char key;
        int count = static_cast<int>(rng) % 100 + 3;
        vector<Point> points;
        for(int i = 0; i < count; i++) {
            Point point;
            point.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
            point.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
            
            points.push_back(point);
        }
        
        if(points.empty()) {
            continue;
        }
        
        vector<int> hull;
        convexHull(points, hull);
        
        
        img = Scalar::all(0);
        for(int i = 0; i < count; i++)
            circle(img, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
        
        int hullcount = static_cast<int>(hull.size());
        Point point0 = points[hull[hullcount - 1]];
        
        for(int i = 0; i < hullcount; i++)
        {
            Point point = points[hull[i]];
            line(img, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
            point0 = point;
        }
        
        imshow("img", img);
        key = static_cast<char>(waitKey());
        if (key == 27 || key == 'q' || key == 'Q')
            break;
        
    }

}

int detect_sharpness(const cv::Mat & image) {
    cv::Mat lap;
    cv::Scalar mu, sigma;
    
    int image_width = image.cols;
    int image_height = image.rows;
    
    if (image_width <= 0 || image_height <= 0) {
        return 0;
    }

    cv::Laplacian(image, lap, CV_64F);
    cv::meanStdDev(lap, mu, sigma);
    return static_cast<int>(sigma.val[0]*sigma.val[0]);
}

void calcHistTest() {
//    cv::Mat le = cv::imread("/Users/hujiawen/Desktop/lenna.jpg", 0);
    cv::Mat le = cv::imread("/Users/hujiawen/Downloads/4489fb70-5c1a-42b9-80ee-823e5dca020e.jpeg", 0);
    

    MatND disHist;
    int dims = 1;
    float hranges[] = { 0, 255 };
    const float *ranges[] = { hranges };
    int size = 256;
    int channels = 0;
    
    calcHist(&le, 1, &channels, Mat(), disHist, dims, &size, ranges);
    int scale = 1;
    
    Mat dstImage(size * scale, size, CV_8U, Scalar(0));
    double minValue = 0;
    double maxValue = 0;
    minMaxLoc(disHist, &minValue, &maxValue, 0, 0);
    
    int hpt = saturate_cast<int>(0.9 * size);
    for (int i = 0; i < 256; i++) {
        float binValue = disHist.at<float>(i);
        int realValue = saturate_cast<int>(binValue * hpt / maxValue);
        rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
        
    }
    
    imshow("yiwei", dstImage);
    
//    cv::Mat rMat = le(cv::Rect(0,0, 100, 100));
    for(int i = 0; i < 1; i++) {
        
        int sharpness = detect_sharpness(le(cv::Rect(0, i * 100, 100, 100)));
        cout << "Sharpness:" << sharpness << endl;
    }
    
    waitKey(0);
}

}

namespace qr_test {

void detect_qr() {
    
    cv::Mat mat;
    cv::Mat img = cv::imread("/Users/hujiawen/Desktop/2.png", cv::IMREAD_COLOR);
    
    
    QRCodeDetector qrDecoder;

    Mat bbox, rectifiedImage;

    std::string data = qrDecoder.detectAndDecode(img, bbox, rectifiedImage);
    if(data.length()>0)
    {
      cout << "Decoded Data : " << data << endl;

      rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
      imshow("Rectified QRCode", rectifiedImage);

      waitKey(0);
    }
    else
      cout << "QR Code not detected" << endl;
    
    
    imshow("qr", img);
    waitKey();
}

}
