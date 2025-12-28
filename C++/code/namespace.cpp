#include <iostream>

    // Namespace = provides a solution for preventing name conflicts 
    //             in large projects. Each entity needs a unique name.
    //             A namespace allows for identical named entities 
    //             as long as the namespaces are different.

using namespace std; //this is the most commonly used but it is considered as a bad practice

namespace first{
    int x = 1;
}
namespace second{
    int x = 2;
}

int main(){

    std::cout << first::x; 
   
    return 0;

}