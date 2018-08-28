//
//  HUOpenCVManager.m
//  HUOpenCV
//
//  Created by jw.hu on 2018/7/25.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

#import "HUOpenCVManager.h"

@implementation HUOpenCVManager

+ (NSString *)openCVVersionString {
    
    return [NSString stringWithFormat:@"OpenCV Version %s",  CV_VERSION];
}



@end
