#include <iostream>

int main(){

    int temp;
    bool sunny = true;

    std::cout << "Enter the temperature: ";
    std::cin >> temp;

    if(temp <= 0 || temp >= 30){//replace || with && 
        std::cout << "The temprature is Bad";
    }
    else 
    {
        std::cout << "The temperature is Good!";
    }

    if(!sunny){
        std::cout << "\nIt's sunny outside!";
    }
    else{
        std::cout << "\nIt's cloudy outside";
    }

    return 0;
}