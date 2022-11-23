/**
 * @file api.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "api.hpp"
#include <iostream>


// Account methods 

std::string Account::get_owner() {
    return owner;
}

int Account::get_total() {
    return total;
}

int Account::deposit(int amount) {
    total += amount;
    return total;
}

int Account::withdraw(int amount) {
    if (total - amount < 0) {
        return 0;
    } else {
        total -= amount;
        return total; 
    }
}

// Credit Card based methods


void Account::activate_credit(int credit_limit) {
    credit_card.set_credentials(get_owner(),credit_limit);
}

int Account::change_credit_limit(int credit_limit) {
    return credit_card.set_credit_limit(credit_limit);
}

int Account::use_credit(int amount_due) {
    return credit_card.add_amount_due(amount_due);
}

int Account::pay_credit_debt(int payment) {
    return credit_card.pay_debt(payment);
}

int Account::get_credit_remaining() {
    return credit_card.get_remaining();
}

int Account::get_amount_due() {
    return credit_card.get_due();
}

int Account::get_credit_limit() {
    return credit_card.get_limit();
}




// Constructor definition
Account::Account(std::string owner_name, int initial_deposit) {
    owner = owner_name;
    total = initial_deposit;
    credit_card.set_credentials(get_owner(), 0);
}

// Destructor definition
Account::~Account() {
    std::cout << "Closing account belonging to " << owner << "\n";
}





// Credit Card methods 

// Constructor
Credit::Credit() {
    owner = "Null";
    credit_limit = 0;
    amount_due = 0;
}

// Destructor
Credit::~Credit() {
    std::cout << "Closing Credit Card belonging to " << owner << "\n";
}

// setters
int Credit::set_credit_limit(int new_limit) {
     credit_limit = new_limit;
     return credit_limit;
}

int Credit::add_amount_due(int amount) {
    // Can't go over credit limit 
    if (amount_due + amount > credit_limit) {
        return 0;
    }
    amount_due += amount;
    return amount_due;
}

int Credit::pay_debt(int amount_paid) {
    amount_due -= amount_due;
    return amount_due;
}

void Credit::set_credentials(std::string owner_name, int credit) {
    owner = owner_name;
    credit_limit = credit;
    amount_due = 0;
}

// getters
int Credit::get_remaining() {
    return credit_limit - amount_due;
}

int Credit::get_due() {
    return amount_due;
}

int Credit::get_limit() {
    return credit_limit;
}

// Investment Account methods

Investing::Investing() {
    cash_amount = 0;
}

Investing::~Investing() {
    std::cout << "Closing Investment Account belonging to " << owner << "\n";
}


// setters
int Investing::deposit_cash(int amount) {
    cash_amount += amount;
    return cash_amount;
}

int Investing::withdraw_cash(int amount) {
    if (amount > cash_amount) {
        return 0;
    }
    cash_amount -= amount;
    return cash_amount;
}


// getters
int Investing::get_cash_amount() {
    return cash_amount;
}