#include <iostream>
void printInfo(const std::string &name,const int &monkage);
int main(){
    
    std::string name = "Juice";
    int age = 16;

    printInfo(name, age);

    return 0;
}
void printInfo(const std::string &name,const int &age){

    std::cout << name << std::endl;
    std::cout << age;
}
/* 
    const parameter ==> parameter that is effectively read only
                        code is more secure & conveys intent 
                        useful for references and pointers 
*/