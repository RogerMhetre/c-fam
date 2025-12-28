#include <iostream>

int main(){

    std::string questions[] =  {"1. What year was C++ created?: ", 
                                "2. Who invented C++?: ",
                                "3. What is the predecessor of C++?: ", 
                                "4. Is the earth flat like her?: "};

    std::string options[][4] = {{"A. 1969 ", "B. 1975 ", "C. 1985 ", "D. 1989"}, 
                                {"A. Guido van Rossum ", "B. Bjarne Stroustrup ", "C. John Carmack ", "D. Mark Zuckerberg"},
                                {"A. C ", "B. GO ", "C. Assembly language ", "D. C+"},
                                {"A. Yes ", "B. NO ", "C. Sometimes ", "D. What's earth?"}};

    char answerKey[] = {'C', 'B', 'A', 'B'};

    int size = sizeof(questions)/ sizeof(questions[0]);
    char guess; 
    int score = 0; 

    for(int i = 0; i < size; i++){
        std::cout << "**********************\n";
        std::cout << questions[i] << '\n';
        std::cout << "**********************\n";

        for(int j = 0; j < sizeof(options[i])/ sizeof(options[i][0]); j++){
            std::cout << options[i][j] << '\n'; 
        }

        std::cin >> guess;
        guess = toupper(guess);

        if(guess == answerKey[i]){
            std::cout << "CORRECT\n";
            score++;
        }else{
            std::cout << "WRONG!\n";
            std::cout << "Answer: " << answerKey[i] << std::endl;
        }
    }

    std::cout << "**********************\n";
    std::cout << "        RESULTS       \n"; 
    std::cout << "**********************\n";

    std::cout << "CORRECT GUESSES: " << score << std::endl;
    std::cout << "# of Questions: " << size << std::endl;
    std::cout << "SCORE: " << (score/(double)size)*100 << "%";

    return 0;
}