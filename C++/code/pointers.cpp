#include <iostream>
 
int main(){

    // pointers ==> variable that stores a memory address of another variable 
    //              sometimes it's easier to work with an address
    
    // & address-of operator
    // * dereference operator 
    
    std::string name = "Juice";
    int age = 21;
    std::string freePizzas[5] = {"pizza1", "pizza2", "pizza3", "pizza4", "pizza5" }

    std::string *pName = &name;
    int *pAge = &age;
    std::string *pfreePizzas = &freePizzas;

    std::cout << *pName << std::endl;
    std::cout << *pAge;

    return 0;
}