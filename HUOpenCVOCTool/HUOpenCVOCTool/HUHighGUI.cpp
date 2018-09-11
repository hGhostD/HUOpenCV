//
//  HUHighGUI.cpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2018/9/10.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#include "HUHighGUI.hpp"
#include <highgui.h>
#include <cv.h>

void my_mouse_callback(int event, int x, int y, int flags, void *param);
CvRect box;
bool drawing_box = false;

void draw_box(IplImage *img, CvRect rect) {
    cvRectangle(img, cvPoint(box.x, box.y), cvPoint(box.x + box.width, box.y + box.height), cvScalar(0x00, 0x00, 0xff));
}

// 鼠标事件
int moveMousePainting() {
    box = cvRect(-1, -1, 0, 0);
    IplImage* image = cvCreateImage(cvSize(1200, 1200), IPL_DEPTH_8U, 3);
    cvSetZero(image);
    
    IplImage* temp = cvCloneImage(image);
    
    cvNamedWindow("Box");
    cvSetMouseCallback("Box", my_mouse_callback, (void *)image);
    while (1) {
        cvCopy(image, temp);
        if (drawing_box) { draw_box(temp, box); }
        cvShowImage("Box", temp);
        
        if (cvWaitKey(15) == 27) { break; }
    }
    
    cvReleaseImage(&image);
    cvReleaseImage(&temp);
    cvDestroyWindow("Box");

    return 0;
}
// 移动鼠标处理
void my_mouse_callback(int event, int x, int y, int flags, void *param) {
    IplImage* image = (IplImage *)param;
    
    switch (event) {
        case CV_EVENT_MOUSEMOVE:
            if (drawing_box) {
                box.width = x - box.x;
                box.height = y - box.y;
            }
            break;
        case CV_EVENT_LBUTTONDOWN:
            drawing_box = true;
            box = cvRect(x, y, 0, 0);
            break;
        case CV_EVENT_LBUTTONUP:
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
        default:
            break;
    }
}
