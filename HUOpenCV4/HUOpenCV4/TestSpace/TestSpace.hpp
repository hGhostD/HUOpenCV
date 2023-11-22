//
//  TestSpace.hpp
//  HUOpenCV4
//
//  Created by 胡佳文 on 2023/3/28.
//  Copyright © 2023 jw.hu. All rights reserved.
//

#ifndef TestSpace_hpp
#define TestSpace_hpp

#include <stdio.h>

void detect_sharpness();
void test_books();
 
namespace mao_book {
void findConvexHull();
void calcHistTest();
}

namespace qr_test {
void detect_qr();
}
#endif /* TestSpace_hpp */
