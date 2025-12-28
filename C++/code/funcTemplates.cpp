#include <iostream>
template <typename T, typename U>

auto max(T x, U y){
    return (x > y) ? x : y;
}

int main(){

    std::cout << max(1.1f, 2.1f);

    return 0;
}
    // Function template = describes what a function looks like.
    //                     Can be used to generate as many overloaded functions 
    //                     as needed, each using different data types
    
    // Example ==> "It's like a cookie cutter'
    //             "Cookies are the same shape but the dough is different" 