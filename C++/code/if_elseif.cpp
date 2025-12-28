#include <iostream>

int main(){
    int age;

    std::cout << "Enter your age: ";
    std::cin >> age;

    if(age > 100){
        std::cout << "You can sleep in your coffin nigga";
    }
    else if(age >= 18){
        std::cout << "Welcome to the site";
    }
    else if(age < 0){
        std::cout << "First come out of your mommy's tomb nigga";
    }
    
    return 0;
}