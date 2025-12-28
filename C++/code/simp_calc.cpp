#include <iostream>

int main(){

    char op;
    double num1;
    double num2;
    double result;

    std::cout << "***************CALCULATOR***************\n";

    std::cout << "Enter either (+ - * /): ";
    std::cin >> op;



    
    if(op != '+' && op != '-' && op != '*' && op != '/'){
        std::cout << "That was an invalid operator";
    }
    else{
        std::cout << "Enter #1: ";
        std::cin >> num1;
    
        std::cout << "Enter #2: ";
        std::cin >> num2;


        switch(op){
            case '+':
                result = num1 + num2;
                std::cout << "RESULT: " << result << std::endl;
                break;
            case '-':
                result = num1 - num2;
                std::cout << "RESULT: " << result << std::endl;
                break;
            case '*':
                result = num1 * num2;
                std::cout << "RESULT: " << result << std::endl;
                break;
            case '/':
                result = num1 / num2;
                std::cout << "RESULT: " << result << std::endl;
                break;
            default:
                std::cout << "That wasn't an valid operator";
        }
    }
    std::cout << "\n***************CALCULATOR***************\n";

    return 0;
}