#include <iostream>

int main(){

    /* sizeof() ==> determines the size in bytes of a: 
                    variables, data type, class, objects, etc.*/
    
    std::string name = "Juice";                
    double gpa = 2.5;
    char grade = 'F';
    bool student = true;
    char grades[] = {'A', 'B', 'C', 'D', 'F'};
    std::string students[] = {"Spongebob", "Patrick", "Squidward"};

    std::cout << sizeof(students)/sizeof(std::string) << " bytes";

    return 0;
}