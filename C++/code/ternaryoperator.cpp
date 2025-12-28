#include <iostream>

int main(){

    //ternary operator ?: = replacement to an if/else statement

    //Syntax:
    //condition ? expression1 : expression2;

    int grade = 75;

    grade >= 60 ? std::cout << "You pass!" : std::cout << "You fail1";

    return 0;
}