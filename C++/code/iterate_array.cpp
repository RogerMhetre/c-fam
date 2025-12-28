// Iterate over an array 
#include <iostream>

int main(){
    
    std::string students[] = {"Juice", "Jahseh", "Kanye", "Roger"};

    for(int i = 0; i < sizeof(students)/sizeof(std::string); i++){
        std::cout << students[i];
        if(i != 3){
            std::cout << std::endl;
        }
    }

    return 0;
}