//
//  ThirdClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2019/12/17.
//  Copyright © 2019 jw.hu. All rights reserved.
//

#include "ThirdClass.hpp"
#include <iostream>
#include <opencv.hpp>

using namespace std;

void learn() {
    cv::RNG rng;
    int a = rng.uniform(0, 100);
    int b = rng.next();
    cout << a << endl << b << endl;
}
