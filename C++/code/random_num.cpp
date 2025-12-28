#include <iostream>
#include <ctime>

int main(){

    // pseudo-random ==> NOT truly random (but close)

    srand(time(NULL)); //time(NULL) ==> current time

    int num1 = (rand() % 20) + 1;
    int num2 = (rand() % 20) + 1;
    int num3 = (rand() % 20) + 1;

    std::cout << num1 << std::endl;
    std::cout << num2 << std::endl;
    std::cout << num3;
    return 0;
}