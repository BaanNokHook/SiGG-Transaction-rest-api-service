/**
 * @file test.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include "api.hpp"

int main() {

    // testing basic account methods
    std::cout << "------------------------------\n";
    std::cout << "Testing basic account methods \n";
    Account Bob("Bob",450);
    std::cout << Bob.get_total() << " is the initial deposit\n";
    std::cout << Bob.get_owner() << " is the name of owner\n";

    std::cout << "Account now has $" << Bob.deposit(450) << "\n";
    std::cout << "Account now has $" << Bob.withdraw(100) << "\n";
    std::cout << "Insufficient funds so $" << Bob.withdraw(1000) << " is shown\n";
    std::cout << "------------------------------\n";
    
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";


    // testing credit card methods 
    std::cout << "------------------------------\n";
    std::cout << "Testing Credit Card Methods\n";
    Bob.activate_credit(300);
    std::cout << Bob.get_credit_remaining() << " is the amount of credit Bob starts with\n";
    std::cout << Bob.use_credit(200) << " is the total amount of credit owed\n";
    std::cout << "Displays " << Bob.use_credit(400) << " since we can't go over the credit limit \n";
    std::cout << "Extending more credit for Bob's credit card so it's now $" << Bob.change_credit_limit(1000) << "\n";
    std::cout << "Bob has this much still available now (after subtracting debts): $" << Bob.get_credit_remaining() << "\n";
    std::cout << "Bob goes out and now has total credit debt of $" << Bob.use_credit(800) << " so now he has available credit of $" << Bob.get_credit_remaining() << "\n"; 
    std::cout << "Pays off $1000 worth of credit so now balance of debt remaining is $" << Bob.pay_credit_debt(1000) << "\n";
    std::cout << "Now, Bob has $" << Bob.get_credit_remaining() << " worth of credit remaining\n";
    std::cout << "Bob has $" << Bob.get_amount_due() << " worth of debt remaining\n";
    std::cout << "Bob has a credit limit of $" << Bob.get_credit_limit() << "\n";

    
    std::cout << "------------------------------\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
}