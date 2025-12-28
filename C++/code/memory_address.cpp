#include <iostream>

int main(){

    // memory address = a location in memory where data is stored 
    // a memory address can accessed with & (address of operator) 

    std::string name = "Roger";
    int age = 20 ;
    bool student = true;

    std::cout << &name << std::endl;
    std::cout << &age << std::endl;
    std::cout << &student ;

    return 0;
}