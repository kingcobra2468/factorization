#ifndef CLI_H
#define CLI_H
#include "stdio.h"
#include <new>
#include <cmath>
#include <array>
#include <valarray>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <forward_list>
#include <list>

class commandLineArg{
    private:
        std::string * expression = new std::string;
        std::list<float> numbers;
        int t = 0;       
    protected:
    public:
        commandLineArg();
        commandLineArg(std::string * stringArg);
        void convertStringtoPoly();
        friend std::list<float> getNumbers(commandLineArg userInput);
};


#endif 