#include <iostream>

int main(){

    std::string name;

    std::cout << "Enter your name: ";
    std::getline(std::cin , name);

    // name.length() 
    // name.empty()  ==> Boolean 
    // name.clear();  ==> The value in name is cleared  
    // name.append("@gmail.com"); ==> appends the string 
    // name.at(index_num) ==> prints the character at the specific index number
    // name.insert(index_num, "@") ==> prints "@" at the specific index number
    // name.find(character to find) ==> Gives the index num of the character
    // name.erase(first_index, last_index) ==> erases the letters in that index 

    name.erase(0,6);

    std::cout << name;

    return 0;
}