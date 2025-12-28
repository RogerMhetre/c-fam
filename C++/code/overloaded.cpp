#include <iostream>
#include <string>

void bakePizza();
void bakePizza(std::string topping1);
void bakePizza(std::string topping1, std::string topping2);

// overloaded function ==> the ability to define multiple functions with the same name
//                         within the same scope, but with different parameter lists

int main(){

    bakePizza("Pepperoni", "bacon");

    return 0;
}

void bakePizza(){
    std::cout << "Here is your pizza"; 
}

void bakePizza(std::string topping1){
    std::cout << "Here is your " << topping1 << " pizza";
}
void bakePizza(std::string topping1, std::string topping2){
    std::cout << "Here is your " << topping1 << " and " << topping2 << " pizza";
}