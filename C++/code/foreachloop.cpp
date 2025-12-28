#include <iostream>

int main(){

    // foreach loop = loop that eases the transversal over an iterable data set
    // it is loop like we use in python just in C++.

    // std::string students[] = {"Juice", "Jahseh", "Kanye", "Roger"};
    int grades[] = {65, 32, 93, 32};


    for(int x : grades){
        std::cout << x << '\n';
    }

    return 0;
}