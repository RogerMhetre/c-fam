#include <iostream>

int main(){

    /* array ==> a data structure that can hold multiple values 
                 values are accessed by an index number
                 kind of like a variable that holds multiple values */

    std::string cars[3]; // declaration

    cars[0] = "Camaro";
    cars[1] = "Mustang";        // Assign values 
    cars[2] = "Bugatti";

    // std::string cars[3] = { "Camaro", "Mustang", "Bugatti"}; # declare + assign

    std::cout << cars[0]<< std::endl; 
    std::cout << cars[1]<< std::endl;
    std::cout << cars[2];

    return 0;
}