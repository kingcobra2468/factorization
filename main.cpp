#include "stdio.h"
#include <new>
#include <cmath>
#include <numeric>
#include <complex>
#include <array>
#include <valarray>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "commandLineIn.h"
#include "factoring.h"

int main(int argc, char * argv[]){
    std::string * temp = new std::string(argv[1]);
    factoring test(temp);
    test.computingFactors();
    test.userOutput();
    return 0;
}