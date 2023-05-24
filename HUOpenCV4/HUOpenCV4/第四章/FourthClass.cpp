//
//  FourthClass.cpp
//  HUOpenCV4
//
//  Created by hu on 2019/12/18.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "FourthClass.hpp"
#include <opencv2/opencv.hpp>

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


namespace chapter_04 {

vector<cv::Mat1b> numbers;
vector<int> numArr;
int index = 0;
cv::Point2d position(20, 20);
int imgWidth = 500;

void init_numbers()
{
    //init numbers
    for (int i = 0; i < 11; i++)
        numbers.push_back(cv::Mat1b::zeros(20, 10));
    //0:
    for (int i = 2; i < 8; i++)
    {
        numbers[0].at<unsigned char>(2, i) = 255;
        numbers[0].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 17; i++)
    {
        numbers[0].at<unsigned char>(i, 2) = 255;
        numbers[0].at<unsigned char>(i, 7) = 255;
    }
    //1:
    for (int i = 2; i < 8; i++)
    {
        numbers[1].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 17; i++)
    {
        numbers[1].at<unsigned char>(i, 5) = 255;
    }
    numbers[1].at<unsigned char>(5, 2) = 255;
    numbers[1].at<unsigned char>(4, 3) = 255;
    numbers[1].at<unsigned char>(3, 4) = 255;
    numbers[1].at<unsigned char>(2, 5) = 255;
    //2:
    for (int i = 2; i < 8; i++)
    {
        numbers[2].at<unsigned char>(2, i) = 255;
        numbers[2].at<unsigned char>(9, i) = 255;
        numbers[2].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 9; i++)
    {
        numbers[2].at<unsigned char>(i, 7) = 255;
    }
    for (int i = 10; i < 17; i++)
    {
        numbers[2].at<unsigned char>(i, 2) = 255;
    }
    //3:
    for (int i = 2; i < 8; i++)
    {
        numbers[3].at<unsigned char>(2, i) = 255;
        numbers[3].at<unsigned char>(9, i) = 255;
        numbers[3].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 9; i++)
    {
        numbers[3].at<unsigned char>(i, 7) = 255;
    }
    for (int i = 10; i < 17; i++)
    {
        numbers[3].at<unsigned char>(i, 7) = 255;
    }
    //4:
    for (int i = 2; i < 8; i++)
    {
        numbers[4].at<unsigned char>(10, i) = 255;
    }
    for (int i = 2; i < 18; i++)
    {
        numbers[4].at<unsigned char>(i, 5) = 255;
    }
    numbers[4].at<unsigned char>(4, 4) = 255;
    numbers[4].at<unsigned char>(5, 4) = 255;
    numbers[4].at<unsigned char>(6, 3) = 255;
    numbers[4].at<unsigned char>(7, 3) = 255;
    numbers[4].at<unsigned char>(8, 3) = 255;
    numbers[4].at<unsigned char>(9, 2) = 255;
    numbers[4].at<unsigned char>(10, 2) = 255;
    //5:
    for (int i = 2; i < 8; i++)
    {
        numbers[5].at<unsigned char>(2, i) = 255;
        numbers[5].at<unsigned char>(9, i) = 255;
        numbers[5].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 9; i++)
    {
        numbers[5].at<unsigned char>(i, 2) = 255;
    }
    for (int i = 10; i < 17; i++)
    {
        numbers[5].at<unsigned char>(i, 7) = 255;
    }
    //6:
    for (int i = 2; i < 8; i++)
    {
        numbers[6].at<unsigned char>(2, i) = 255;
        numbers[6].at<unsigned char>(9, i) = 255;
        numbers[6].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 17; i++)
    {
        numbers[6].at<unsigned char>(i, 2) = 255;
    }
    for (int i = 10; i < 17; i++)
    {
        numbers[6].at<unsigned char>(i, 7) = 255;
    }
    //7:
    for (int i = 2; i < 8; i++)
    {
        numbers[7].at<unsigned char>(2, i) = 255;
    }
    for (int i = 3; i < 6; i++)
    {
        numbers[7].at<unsigned char>(i, 7) = 255;
    }
    for (int i = 6; i < 10; i++)
    {
        numbers[7].at<unsigned char>(i, 6) = 255;
    }
    for (int i = 10; i < 14; i++)
    {
        numbers[7].at<unsigned char>(i, 5) = 255;
    }
    for (int i = 14; i < 18; i++)
    {
        numbers[7].at<unsigned char>(i, 4) = 255;
    }
    //8:
    for (int i = 2; i < 8; i++)
    {
        numbers[8].at<unsigned char>(2, i) = 255;
        numbers[8].at<unsigned char>(9, i) = 255;
        numbers[8].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 17; i++)
    {
        numbers[8].at<unsigned char>(i, 2) = 255;
    }
    for (int i = 3; i < 17; i++)
    {
        numbers[8].at<unsigned char>(i, 7) = 255;
    }
    //9:
    for (int i = 2; i < 8; i++)
    {
        numbers[9].at<unsigned char>(2, i) = 255;
        numbers[9].at<unsigned char>(9, i) = 255;
        numbers[9].at<unsigned char>(17, i) = 255;
    }
    for (int i = 3; i < 17; i++)
    {
        numbers[9].at<unsigned char>(i, 7) = 255;
    }
    for (int i = 3; i < 10; i++)
    {
        numbers[9].at<unsigned char>(i, 2) = 255;
    }
}
 
void help()
{
    cout << "Please Input numbeer'0'-'9'" << endl;
}

void updatePosition(int i) {
    int x = i * 10 + 20;
    int y = 0;
    
    y = x / (imgWidth - 40) * 20 + 20;
    x = x % (imgWidth - 40);
    
    position.x = x;
    position.y = y;
}
// 绘制图片到 Mat
void draw(cv::Mat mat) {
    cv::Mat1b empty = cv::Mat1b::zeros(imgWidth, imgWidth);
    empty.copyTo(mat);
    for(int i = 0; i < numArr.size(); i++) {
        updatePosition(i);
        cv::Mat tmp = mat.rowRange(position.y, position.y + 20).colRange(position.x, position.x + 10);
        numbers[numArr[i]].copyTo(tmp);
    }
}

int addNum(int arrNum, int changeNum) {
    arrNum += changeNum;
    if (arrNum < 0) arrNum = 9;
    if (arrNum > 9) arrNum = 0;
    return arrNum;
}

void test_01_a() {
    help();
    // 创建 500 * 500 黑色背景图片
    cv::Mat1b mat = cv::Mat1b::zeros(imgWidth, imgWidth);
    imshow("1b", mat);
    // 创建 vector 数组 存放数字图片 0~9
    init_numbers();
    // 循环 捕获键盘输入
    int a = 0;
    while (a != 27) {
        // 根据键盘输入进行逻辑判断
        /**
                    
         1. 输入 0~9 在下一个位置放置数字图片
         2. 输入 上下左右 就调整位置
         3. 输入 ESC 结束程序
         
         创建一个数组用了存储数字,以及当前光标位置
         */
        a = waitKey();
        if (a > 47 && a < 58) {
            numArr.push_back(a - 48);
            index++;
        }
        
        if (a == 127) {
            index--;
            cout << "删除:" << index << endl;
            if (index > 0) {
                numArr.erase(numArr.begin() + index);
            } else if (index == 0) {
                numArr.erase(numArr.begin());
                index = 0;
            } else {
                index = 0;
            }
        }
        
        if (a >= 0 && a <= 3) {
            if (a == 0 && (index < numArr.size())) {
                int n = numArr[index];
                numArr[index] = addNum(n, 1);
            } else if (a == 1 && index < numArr.size()) {
                int n = numArr[index];
                numArr[index] = addNum(n, -1);
            } else if (a == 2) {
                index--;
                if (index < 0 ) index = 0;
            } else if (a == 3) {
                index++;
                if (index > numArr.size()) index = static_cast<int>(numArr.size());
            }
        }
        
        for (auto i : numArr) cout << i;
        cout << endl;
        
        draw(mat);
        imshow("1b", mat);
    }
}

void test_02() {
    cv::RNG rng(time(0));
    cv::Mat1b mat(200, 100);
    rng.fill(mat, cv::RNG::UNIFORM, 0, 255);
    int sum = cv::sum(mat)[0];
    mat /= sum;
    imshow("m", mat);
//    cout << mat /= sum << endl;
    waitKey();
}
void test() {
//    test_01_a();
    test_02();
}
}
