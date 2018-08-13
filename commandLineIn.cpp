#include "stdio.h"
#include <new>
#include <cmath>
#include <list>
#include <string>
#include <algorithm>
#include "commandLineIn.h"
#include <ctype.h>
#include <stdlib.h>
#include "/home/erik/Documents/Programming/CPP/Library/myFunction.h"
#include <iterator>

    commandLineArg::commandLineArg(){
    };

    commandLineArg::commandLineArg(std::string * stringArg) : expression(stringArg){
        this->convertStringtoPoly();
};

    void commandLineArg::convertStringtoPoly(){
        methods * convert = new methods();
        char * x = new char; 
        std::forward_list<char> * holdFiltered = new std::forward_list<char>;
        for(char chr : *expression){
            if ((chr >= 65 && chr <= 90) || (chr >= 97 && chr <= 122)) {x=&chr; break;}  
        }
        holdFiltered = convert->removeInString(expression, *x, true); //pointer
        delete convert;
        std::string buildingNum;
        signed short numInverter = 1;
        int i = 0;
        std::list<float>::iterator marker = numbers.begin(); //WONT STORE NUMBERS GREATER THAN 9 MULTI-DIGIT NUMBERS
        if(holdFiltered->front() == '^'){numbers.insert(numbers.begin(),1);};
        while(!holdFiltered->empty()){
            if(!isdigit(holdFiltered->front())){ //elements over ten stored as two
                switch(holdFiltered->front()){
                    case '+':
                        numInverter = 1; break;
                    case '-':
                        numInverter = -1; break;
                    case '^':
                        while(true){holdFiltered->pop_front();if(holdFiltered->front() != '+' || holdFiltered->front() != '-'){break;};}; //very strange how critea in if loop doesnt work in while loop
                        break;
                }
                buildingNum.clear(); 
                holdFiltered->pop_front();
                
            }

            else{
                while(isdigit(holdFiltered->front()) && holdFiltered->front() != '`'){
                    buildingNum+=holdFiltered->front();
                    holdFiltered->pop_front();
                }
                numbers.insert(marker,numInverter*std::stof(buildingNum));
            }
        }
        if(numbers.size() == 2){
            numbers.insert(++numbers.cbegin(), 0 );
        }
    }


    

