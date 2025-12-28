#include <iostream>
#include <string>
using namespace std;


void reverseString(string str);

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    cout << "Reversed string: ";
    reverseString(s);
    cout << endl;

    return 0;
}
void reverseString(string str) {
    if (str.length() == 0) {       // base case: empty string
        return;
    }
    cout << str.back();             // print last character
    reverseString(str.substr(0, str.length() - 1));  // recursive call on rest
}
