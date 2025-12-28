//Pass struct as arguments 
#include <iostream>

struct Car{
    std::string model;
    int year;
    std::string color;
};
void printCar(Car &car);
int main(){

    Car car1;
    Car car2;

    car1.model = "Mustang";
    car1.year = 2023;
    car1.color = "Black";

    car2.model = "lambo";
    car2.year = 2022;
    car2.color = "Purple";

    printCar(car1);
    std::cout << std::endl;
    printCar(car2);

    return 0;
}
void printCar(Car &car){
    std::cout << &car << '\n';
    std::cout << car.model << std::endl;
    std::cout << car.year << std::endl;
    std::cout << car.color ;
}