#include <iostream>

int main(){

    std::string *pGrades = nullptr;
    int size; 

    std::cout << " How many grades to enter in?: ";
    std::cin >> size;

    pGrades = new std::string[size];

    for(int i = 0; i < size; i++){
        std::cout << "Enter grade #" << i + 1 << " : ";
        std::cin >> pGrades[i];
    }
    
    for(int i = 0; i < size; i++){
        std::cout << pGrades[i] << " ";
    }

    delete[] pGrades;

    return 0;
}
    // dynamic memory = Memory that is allocated after the program 
    //                  is already compiled and running. 
    //                  Use the 'new' operator to allocate 
    //                  memory in the heap rather than the stack 

    //                  Useful when we don't know how much memory we will need. 
    //                  Makes our program more flexible, especially 
    //                  when accepting user input.