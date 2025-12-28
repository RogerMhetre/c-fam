//Typedef and type aliases

//typedef = reserved keyword to create an additional name
    //          (alias) for another data type.
    //          New identifier for an existing type 
    //          Helps with readability and reduces typos 

#include <iostream>
#include <vector>

//typedef std::vector<std::pair<std::string , int>> pairlist_t;     //commonly used 
typedef std::string type_t;
typedef int number;     //it is okay if we not use _t 
                        //it's just a hint that score_t is a type 
                        //it just helps readability 

//we can use 'using' instead of 'typedef'
//Syntax:
using number = int;  

int main(){

    std::string firstname = "Roger";
    std::cout << "My firstname is "<< firstname << '\n';

    type_t lastname = "Mhetre";     //replaced std::string with type_t 
    std::cout << "My last name is "<< lastname << std::endl;

    number age = 17;        
    std::cout << "My age is "<< age ;

    return 0;
}