// ROCK PAPER SCISSORS
#include <iostream>
#include <ctime>
#include <cctype>
#include <limits>

char getUserChoice();
char getComputerChoice();
void showChoice(char choice);
void choosewinner(char player, char computer);

int main(){
    char player;
    char computer;

    player = getUserChoice();
    std::cout << "Your Choice: \n";
    showChoice(player);

    computer = getComputerChoice();
    std::cout << "Computer's Choice: \n";
    showChoice(computer);

    choosewinner(player, computer);


    return 0;
}
char getUserChoice(){
    char player;
    std::cout << "+++++++++++++++++++++++++\n";
    std::cout << "Rock-Paper-Scissors Game!\n";

    do{
        std::cout << "Choose one of the following\n";
        std::cout << "+++++++++++++++++++++++++\n";
        std::cout << "'r' for Rock\n";
        std::cout << "'p' for Paper\n";
        std::cout << "'s' for Scissors\n";
        std::cin >> player;

        player = std::tolower(player);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        /*  this is like a limit to skip or ignore the characters stored in the buffer
            and streamsize is a special integer type that can hold many number
            so streamsize get the number of character to skip in the buffer 
            like because of the \n in the last the ignore keyword tells when ever we see a newline 
            flush everything after it cause after it a newline gets stored due to the keyword 'enter'
            cause when we press "enter" a newline gets generated and if the newline is read before the 
            next input it takes this "enter i.e \n" has an input and gives and empty string as an output */

    }while(player != 'r' && player != 'p' && player != 's');

    return player;
}
char getComputerChoice(){

    srand(time(NULL));
    int num = rand() % 3 + 1;

    switch(num){
        case 1: return 'r';
        case 2: return 'p';
        case 3: return 's';
    }
    return 0;
}
void showChoice(char choice){
    switch(choice){
        case 'r': std::cout << "Rock\n";
            break;
        case 'p': std::cout << "Paper\n";
            break;
        case 's': std::cout << "Scissors\n";
            break;
    }
}
void choosewinner(char player, char computer){
    switch(player){
        case 'r':   if(computer == 'r'){
                        std::cout << "It's a TIE\n";
                    }
                    else if(computer == 'p'){
                        std::cout << "You lose!\n";
                    }
                    else{
                        std::cout << "You win!\n";
                    }
                    break;
        case 'p':   if(computer == 'r'){
                        std::cout << "You win!\n";
                    }
                    else if(computer == 'p'){
                        std::cout << "It's a TIE!\n";
                    }
                    else{
                        std::cout << "You lose!\n";
                    }
                    break; 
        case 's':   if(computer == 'r'){
                        std::cout << "You lose!\n";
                    }
                    else if(computer == 'p'){
                        std::cout << "You win!\n";
                    }
                    else{
                        std::cout << "It's a TIE!\n";
                    }
                    break; 
    };
}