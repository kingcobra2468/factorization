#ifndef FACTORING_H
#define FACTORING_H
#include "stdio.h"
#include <new>
#include <cmath>
#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include <forward_list>
#include <list>
#include <complex>
#include "commandLineIn.h"


class factoring{
    private:
        std::list<float> numbersForPoly;
        commandLineArg userInput;
        std::list<std::complex<float>> roots;
    public:
        factoring(std::string * stringArg);
        float findFactors();
        float largestNum(std::list<float> numList);
        bool isFloat(float input);
        void computingFactorsX2();
        void computingFactors();  
        bool syntheticDivision(float factor);  
        void userOutput();
};



#endif