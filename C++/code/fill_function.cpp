#include <iostream>

int main(){

    // fill ==> Fills a range of elements with a specified value 
    // fill(begin, end, value)  >> syntax

    const int size = 3;
    std::string foods[size];

    fill(foods, foods + (size/2), "water");
    fill(foods + (size/2), foods + size, "cocaine");

    for(int i = 0; i < size; i++){
        std::cout << foods[i];
        if(i != size - 1){
            std::cout << std::endl;
        }
    }

    return 0;
}