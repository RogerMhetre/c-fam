#include <iostream>

int main(){

    int x; //declaration
    x = 5; //assignment

    std::cout << x ; //basic method to print

    std::cout << '\n'; //method to print new line 

    //integer (whole numbers)
    int age = 17;
    int year = 2025; 

    //double (number including decimals)
    double price = 29.123;
    double gpa = 2.5;

    //char (single character) it should be in single quote ('__')
    char grade = 'A';
    char currency = '$';

    //bool - boolean (just true or false) mostly used in if-elif stat
    bool virgin = true;
    bool forsale = false;

    //string (Stores many character)
    std::string email = "roger123@gmail.com";
    std::string name = "Bro";

    std::cout << "Hello " << name << '\n'; // your name would be continued after Hello
    std::cout << "You are " << age << " years old";

    return 0;
}