#include <iostream>

void happyBirthday(std::string name, int age); // Declaration

int main(){

    // function = a block of reusable code 

    std::string name = "Juice";
    int age = 17;

    happyBirthday(name, age);


    return 0;
}
void happyBirthday(std::string name, int age){  // Defined 
    std::cout << "Happy Birthday to " << name << '\n';
    std::cout << "Happy Birthday to " << name << '\n';
    std::cout << "Happy Birthday dear " << name << '\n';
    std::cout << "Happy Birthday to " << name << "\n";
    std::cout << "You are " << age << " years old!!\n";
}






