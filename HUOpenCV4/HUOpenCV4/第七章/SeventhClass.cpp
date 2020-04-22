//
//  SeventhClass.cpp
//  HUOpenCV4
//
//  Created by jw.hu on 2020/3/26.
//  Copyright © 2020 jw.hu. All rights reserved.
//

#include "SeventhClass.hpp"
#include <opencv.hpp>
using namespace cv;
using namespace std;

void lean_RNG() {
    RNG rng = theRNG();
    
    cout << "(int)rng:" << (int)rng << endl;
    cout << "int(rng):" << int(rng) << endl;
    cout << "(float)rng:" << (float)rng << endl;
    cout << "float(rng):" << float(rng) << endl;
    
    
    RNG uniformRNG = RNG();
    int uniform = uniformRNG.uniform(1, 10);
    cout<< "uniform:" << uniform << endl;
}
