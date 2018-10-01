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

//FINDS LARGEST NUMBER

float factoring::largestNum(std::list<float> numList){
    float largestNum;
    for(std::list<float>::const_iterator start = numbersForPoly.begin();
        start != numbersForPoly.cend();
        start++){
        largestNum < *start ? largestNum = *start : largestNum = largestNum; //find pass in ternary operator
    }
    return largestNum;

}

//CHECKS IF NUMBER IS A FLOAT

bool factoring::isFloat(float input){
    return fmod(input, 1) != 0.0 ? true : false;
}

// PERFORMS SYNTHETIC DIVISION

bool factoring::syntheticDivision(float factor, bool write){
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
    if(write){
        if (remainder == 0) {numbersForPoly = tempNums;};
        roots.push_back({factor, 0});
    }
    
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

    for(float i = 0; i <= largestNum(numbersForPoly); i += 1){ 
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
    } 

    if(numbersForPoly.size() == 3){
        for(std::list<float>::iterator start = numbersForPoly.begin();
            start != numbersForPoly.end();
            ++start){
                *start /= commonFactor;
        }
    }
    //printf("Common Factor: %f\n", commonFactor);
    return commonFactor;
}

//FINISH WORKING ON THIS

std::string factoring::polynomilizeRemainder(){
    if(numbersForPoly.empty()){
        return "";
    }
    else{
        std::string buildingingPoly = "(";
        short remainderSize = numbersForPoly.size();
        for(float coefficient : numbersForPoly){
            if(remainderSize > 1){
                if(coefficient < 0){
                    buildingingPoly+= "-" + std::to_string((int)coefficient) + "x^" + std::to_string(remainderSize-1);
                }
                else{
                    if(remainderSize == numbersForPoly.size()){
                        buildingingPoly+= std::to_string((int)coefficient) + "x^" + std::to_string(remainderSize-1);
                    }
                    else{
                        buildingingPoly+= "+" + std::to_string((int)coefficient) + "x^" + std::to_string(remainderSize-1);
                    }

                }
            }
            else{
               if(coefficient < 0){
                    buildingingPoly+= "-" + std::to_string((int)coefficient) + ")";
                }
                else{
                    buildingingPoly+= "+" + std::to_string((int)coefficient)+ ")";
                }
            }
        remainderSize--;
        }
        
        return buildingingPoly;
    }
}   

void factoring::computingFactors(){

    numbersForPoly = getNumbers(userInput);

    
    bool noFactors = false;

    while(true){
        for(auto x : numbersForPoly){
        std::cout << x << std::endl;
        }
        for(auto x : roots){
        std::cout << x << std::endl;
        }
        if(numbersForPoly.size() > 3 ){
            //if (factoring::findFactors() == 1 && factoring::syntheticDivision(factoring::findFactors())){
            //
            //}
            if(!factoring::syntheticDivision(factoring::findFactors(), false)){
                printf("Cannot be factored\n"); //Make method Factored Remaining
                break;
            }
            factoring::syntheticDivision(factoring::findFactors(), true);
        }
        else if(numbersForPoly.size() <= 3){
            factoring::computingFactorsX2();
            break;
        }
    }
    //if(noFactors){factoring::computingFactorsX2();};
    
}

void factoring::computingFactorsX2(){
    bool mri;
    typedef struct abcxComponenets{
        float a,b,c;
    } elements; 
    elements polyElements; 
    std::list<float>::const_iterator beginList = numbersForPoly.cbegin();
    if (numbersForPoly.size() == 3){
        polyElements.a = *beginList; beginList++;
        polyElements.b = *beginList; beginList++;
        polyElements.c = *beginList;
    }  
    std::cout << polyElements.a << " " << polyElements.b << " " << polyElements.c << std::endl;                  
    (pow(polyElements.b,2)-(4*(polyElements.a * polyElements.c))) >= 0  || polyElements.b == 2 ? mri = true : false;

    auto quadraticFormula = [](elements constants, int Operator){ //lambda
        return ((-1 * constants.b ) + (Operator * sqrt(pow(constants.b,2)-(4*(constants.a * constants.c))))) / (2 * constants.a);};
    if(mri){
        if(std::to_string(quadraticFormula(polyElements, -1)).substr(std::to_string(quadraticFormula(polyElements, -1)).find(".")).size() < 3){
            roots.push_back({quadraticFormula(polyElements, -1), 0.0});
            roots.push_back({quadraticFormula(polyElements, 1), 0.0});
            numbersForPoly.clear();
        }  
    }
    else{
    (roots.push_back({(-1 * polyElements.b ) / (2 * polyElements.a), sqrt(-1*(pow(polyElements.b,2)-(4*(polyElements.a * polyElements.c))))/ (2 * polyElements.a)}),
    (roots.push_back({(-1 * polyElements.b ) / (2 * polyElements.a), -1*sqrt(-1*(pow(polyElements.b,2)-(4*(polyElements.a * polyElements.c))))/ (2 * polyElements.a)})),
    numbersForPoly.clear());
    }
}

void factoring::userOutput(){
    std::string * factored = new std::string;
    int i = 0;
    std::string operatr = "+";
    for(auto x : roots){
        -1*x.real() > 0 || x.imag() > 0 ? operatr="+" : operatr="-";
        if(x.imag() == 0){
            factored->insert(factored->size(),(("( x " + operatr + " ") + std::to_string(abs(x.real())) + " )"));
        }
        else{
            factored->insert(factored->size(),(("( " + std::to_string((int)x.real()) + "x "  + operatr + " ") +  std::to_string((int)x.imag()) + "i )" ));
        }
    }
    printf("%s %s\n", factored->c_str(), factoring::polynomilizeRemainder().c_str());
        for(auto x : roots){
            printf("Root: (real) %f (imag) %f \n", x.real(),x.imag());
    }
}
