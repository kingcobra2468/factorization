#include "stdio.h"
#include <new>
#include <cmath>
#include <array>
#include <iostream>
#include <string>
#include <forward_list>
#include <list>
#include <complex>
#include "commandLineIn.h"
#include "factoring.h"


factoring::factoring(std::string * stringArg) : userInput(stringArg){
}

std::list<float> getNumbers(commandLineArg input){
    commandLineArg * retrieveNms = &input;
    return retrieveNms->numbers;
}

float factoring::largestNum(std::list<float> numList){
    float largestNum;
    for(std::list<float>::const_iterator start = numbersForPoly.begin();
        start != numbersForPoly.cend();
        start++){
        largestNum < *start ? largestNum = *start : largestNum = largestNum; //find pass in ternary operator
    }
    return largestNum;

}

bool factoring::isFloat(float input){
    return fmod(input, 1) != 0.0 ? true : false;
}

bool factoring::syntheticDivision(float factor){
    std::list<float> tempNums;
    factor*=-1;
    int * first = new int;
    *first = 1;
    float remainder;
    std::list<float>::iterator itertor  = tempNums.begin();
    float checkForRemainder = tempNums.front();
    for(auto element : numbersForPoly){
        1 == *first ? remainder = numbersForPoly.front() : remainder = (element + (factor * remainder));
        *first++;
        if(remainder != 0){tempNums.insert(itertor, remainder);};
    }
    if (remainder == 0) {numbersForPoly = tempNums;};
    roots.push_back({factor, 0});
    return remainder == 0 ? true : false;
}


float factoring::findFactors(){

    float commonFactor;
    int workingInElements;
    std::list<float> tempNumbersForPoly;
    tempNumbersForPoly.assign(numbersForPoly.begin(), numbersForPoly.end());
    if(tempNumbersForPoly.size() > 3 && tempNumbersForPoly.front() == 1){
        tempNumbersForPoly.pop_front();
    }
    for(float i = 0; i <= largestNum(numbersForPoly); i += 1){ //SOMETHING IS BROKEN IN THIS FOR LOOP FIX AND DEBUG
        workingInElements = 0;
        for(std::list<float>::const_iterator start = tempNumbersForPoly.begin();
        start != tempNumbersForPoly.cend(); 
        start++){
            float tempNum = *start/i;
            !isFloat(tempNum) ? workingInElements++: workingInElements = workingInElements;
            if(tempNumbersForPoly.size() == workingInElements){
                commonFactor = i;
            };
        }
    } //x2+4x+4 * x+2      x3+4x2+4x_2x2+8x+8 = x3+6x2+12x+8
if(numbersForPoly.size() == 3){
    for(std::list<float>::iterator start = numbersForPoly.begin();
        start != numbersForPoly.end();
        ++start){
            *start /= commonFactor;
        }
    }
    return commonFactor;
}

void factoring::computingFactors(){
    numbersForPoly = getNumbers(userInput);
    bool noFactors = false;
    while(true){
        if(numbersForPoly.size() >= 3 ){
            if (factoring::findFactors() == 1){
                break;
            }
            else if(!factoring::syntheticDivision(factoring::findFactors())){
                printf("Cannot be factored\n");
                break;
            }
        }
        else if(numbersForPoly.size() <= 3){
            factoring::computingFactorsX2();
            break;
        }
    }
    if(noFactors){factoring::computingFactorsX2();};
    
}

void factoring::computingFactorsX2(){
    bool mri;
    typedef struct abcxComponenets{
        float a,b,c;
    } elements; 
    elements polyElements; //1 7 10                -7 + 49 -40 /20 
    //roots Roots;
    std::list<float>::const_iterator beginList = numbersForPoly.cbegin();
    if (numbersForPoly.size() == 3){
        polyElements.a = *beginList; beginList++;
        polyElements.b = *beginList; beginList++;
        polyElements.c = *beginList;
    }                    
    (pow(polyElements.b,2)-(4*(polyElements.a * polyElements.c))) > 0  || polyElements.b == 2 ? mri = true : false;
    
    auto quadraticFormula = [](elements constants, int Operator){
        return ((-1 * constants.b ) + (Operator * sqrt(pow(constants.b,2)-(4*(constants.a * constants.c))))) / (2 * constants.a);};
    mri ?
    (roots.push_back({quadraticFormula(polyElements, -1), 0.0}),
    roots.push_back({quadraticFormula(polyElements, 1), 0.0})) : 
    (roots.push_back({(-1 * polyElements.b ) / (2 * polyElements.a), sqrt(-1*(pow(polyElements.b,2)-(4*(polyElements.a * polyElements.c))))/ (2 * polyElements.a)}),
    (roots.push_back({(-1 * polyElements.b ) / (2 * polyElements.a), sqrt(-1*(pow(polyElements.b,2)-(4*(polyElements.a * polyElements.c))))/ (2 * polyElements.a)})));
    for(auto x : roots){
        std::cout << "ROOT: " << x << std::endl;
    }
}

void factoring::userOutput(){
    std::string * factored = new std::string;
    int i = 0;
    for(auto x : roots){
        
    }
}
