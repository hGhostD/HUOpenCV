//
//  HUMatchTemplate.cpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2024/2/19.
//  Copyright © 2024 jw.hu. All rights reserved.
//

#include "HUMatchTemplate.hpp"

namespace HUMatch {
void test() {
    // 读取源图像和目标图像
    cv::Mat src = cv::imread("/Users/hujiawen/Downloads/def9f2a2-c644-4a38-84e9-3b52c4125d2f.jpeg", 1);
    cv::Mat tem = cv::imread("/Users/hujiawen/Downloads/tmp.jpg", 1);
    cv::resize(tem, tem, cv::Size(tem.cols / 2, tem.rows / 2));
    // 创建结果图像
    cv::Mat resultImage;

    // 进行模板匹配
    cv::matchTemplate(src, tem, resultImage, cv::TM_CCOEFF_NORMED);
    cv::normalize(resultImage, resultImage, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());


    // 设置匹配阈值
    double threshold = 0.6;

    while (true)
    {
        // 获取匹配结果的最大值和位置
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
        std::cout << threshold << std::endl;
        // 如果最大值低于阈值，则停止匹配
        if (maxVal < threshold)
            break;

        // 绘制矩形框标记匹配位置
        cv::Rect boundingBox(maxLoc.x, maxLoc.y, tem.cols, tem.rows);
        cv::rectangle(src, boundingBox, cv::Scalar(0, 255, 0), 2);

        // 将已匹配的区域置为零，以便下一次迭代找到下一个最佳匹配
        cv::floodFill(resultImage, maxLoc, cv::Scalar(0), 0, cv::Scalar(0.1), cv::Scalar(1.0));

    }

    // 显示源图像和标记的结果
    cv::imshow("Source Image", src);
    cv::waitKey(0);

    
}
}

