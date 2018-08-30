//
//  HUChangeImageTool.hpp
//  HUOpenCVOCTool
//
//  Created by jw.hu on 2018/8/29.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#ifndef HUChangeImageTool_hpp
#define HUChangeImageTool_hpp

#include <stdio.h>

void example(IplImage* image);

void roiAdd(const char* fileName, const char* roi_x, const char* roi_y, const char* roi_width, const char* roi_height, const char* roi_add);
#endif /* HUChangeImageTool_hpp */
