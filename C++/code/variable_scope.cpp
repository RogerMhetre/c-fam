#include <iostream>

void printNum(int myNum);

int myNum = 3; //global variable #not secure

int main(){
    // Local variables = declared inside a function or block {}
    // Global variables = declared outside of all functions 

    int myNum = 1;      // local variable   

    printNum(myNum);
    
    return 0;
}

void printNum(int myNum){
    std::cout << ::myNum ;      // :: = scope resolution operator to call global var
}
