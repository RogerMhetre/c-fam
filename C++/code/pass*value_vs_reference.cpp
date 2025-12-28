// PASS BY VALUE vs PASS BY REFERENCE 
#include <iostream>

void swap(std::string &x, std::string &y);

int main(){

    std::string x = "Juice";
    std::string y = "Water";

    swap(x, y);

    std::cout <<"X: "<< x << '\n';
    std::cout << "Y: " << y << std::endl;

    return 0;
}
void swap(std::string &x, std::string &y){
    std::string temp;
    
    temp = x; 
    x = y; 
    y = temp;
}
/*
In pass by value the og value is passed to a new varible to make the things work out.
In pass by reference the og variable is passed to make the things work out.
So here the new variable, that is only a copy of the og is swapped but the og is not swapped 
so just by referencing the og by using (&) we can swap the og and not the copy 

#but when do we use pass by value  
We use pass by value when we are returning the value again to the main function 
And the returning data type should match the function data type 
*/