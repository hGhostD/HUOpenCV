//
//  NinthClass.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/4/3.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#include "NinthClass.hpp"


Rect box;
bool drawing_box = false;

void draw_box(Mat &img, Rect box) {
    rectangle(img, box.tl(), box.br(), Scalar(0, 0, 255));
}

void showWindows_9() {
    
    box = Rect(-1,-1,0,0);
    Mat image(200, 200, CV_8UC3), temp;
    image.copyTo(temp);
    
    image = Scalar::all(0);
    
    namedWindow("Box Ex");
    setMouseCallback("Box Ex", my_mouse_callback, (void*)&image);
    
    for(;;) {
        image.copyTo(temp);
        if (drawing_box) draw_box(temp, box);
        imshow("Box Ex", temp);
        if (waitKey(15) == 27) break;
    }
    
    
//    Mat lenna = imread("/Users/hujiawen/Desktop/lenna.jpg", cv::IMREAD_GRAYSCALE);
//    imshow("lenna", lenna);
//    waitKey(27);
}

void my_mouse_callback(int event, int x, int y, int flags, void *param) {
    Mat &image = *(Mat*) param;
    switch (event) {
        case EVENT_MOUSEMOVE: {
            if (drawing_box) {
                box.width = x - box.x;
                box.height = y - box.y;
            }
            break;
        }
        case EVENT_LBUTTONDOWN: {
            drawing_box = true;
            box = Rect(x, y, 0, 0);
            break;
        }
        case EVENT_LBUTTONUP: {
            drawing_box = false;
            if (box.width < 0) {
                box.x += box.width;
                box.width *= -1;
            }
            if (box.height < 0) {
                box.y += box.height;
                box.height *= -1;
            }
            draw_box(image, box);
        }
        default:
            break;
    }
}

