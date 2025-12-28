#include <iostream>

int main(){

    // type conversion = conversion a value of one data type to another 
    //                   Implicit = automatic 
    //                   Explicit = Precede value with new data(int)

    int correct = 8;
    int questions = 10;
    double score = correct/(double)questions * 100;

    //type conversion is to make the output as per our requirement and to store data

    Syntax:
    Og data_type variable_name = (new_data_type) variable_name;

    std::cout << score <<'%';

    

    return 0;
}