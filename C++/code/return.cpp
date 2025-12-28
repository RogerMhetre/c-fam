#include <iostream>

double square(double length);

int main(){

    /* return = return a value back to the spot 
                where you called the encompassing function */

    double length = 5.0;
    double area = square(length);
    
    std::cout << "Area: " << area << "cm²\n";

    return 0;
}
double square(double length){
    return length * length; 
}