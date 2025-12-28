#include <iostream>

int main(){

    

    while(true){
        int month;
        std::cout << "Enter the month (1-12): ";
        std::cin >> month;

        switch(month){
            case 1:
                std::cout << "It is January";
                return 0;
            case 2:
                std::cout << "It is February";
                return 0;
            case 3:
                std::cout << "It is March";
                return 0;
            case 4:
                std::cout << "It is April";
                return 0;
            case 5:
                std::cout << "It is May";
                return 0;
            case 6:
                std::cout << "It is June";
                return 0;
            case 7:
                std::cout << "It is July";
                return 0;
            case 8:
                std::cout << "It is August";
                return 0;
            case 9:
                std::cout << "It is September";
                return 0;
            case 10:
                std::cout << "It is October";
                return 0;
            case 11:
                std::cout << "It is November";
                return 0;
            case 12:
                std::cout << "It is December";
                return 0;
            default:
                std::cout << "Please enter only numbers from 1 - 12" << std::endl;
        }
    }   

    return 0;
} 