#include <iostream>
#include <string>

int main() {
    int n = 7;   // size of one X
    int count = 3; // how many X's in a row

    for(int i = 0; i < n; i++) { // row loop
        for(int k = 0; k < count; k++) { // how many Xs
            for(int j = 0; j < n; j++) { // column of one X
                if(j == i || j == n - i - 1) {
                    std::cout << '*';
                } else {
                    std::cout << ' ';
                }
            }
            std::cout << ' '; // space between X's
        }
        std::cout << std::endl;
    }

    return 0;
}