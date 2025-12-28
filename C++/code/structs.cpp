#include <iostream> 

struct student{
    std::string name;
    double gpa;
    bool enrolled = true;
};

int main(){

    student student1;
    student1.name = "Juice";
    student1.gpa = 3.2;
    
    student student2;
    student2.name = "Jahseh";
    student2.gpa = 2.1;

    student student3;
    student3.name = "Kanye";
    student3.gpa = 1.5;

    std::cout << student1.name << std::endl;
    std::cout << student1.gpa << std::endl;
    std::cout << student1.enrolled << std::endl;

    std::cout << student2.name << std::endl;
    std::cout << student2.gpa << std::endl;
    std::cout << student2.enrolled << std::endl;

    std::cout << student3.name << std::endl;
    std::cout << student3.gpa << std::endl;
    std::cout << student3.enrolled ;

    return 0;
}
// struct = A structure that group related variable under one name 
//          structs can contain many different data types 
//          variables in a struct are known as members 
//          members can be access with. "Class member Access operator"