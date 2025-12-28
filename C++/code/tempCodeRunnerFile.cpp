    std::cout <<   "Your balance is: $"<< std::setprecision(2) << std::fixed << balance << std::endl;
}
double deposit(){

    double amount = 0;

    std::cout << "Enter amount to be deposited: ";
    std::cin >> amount;
