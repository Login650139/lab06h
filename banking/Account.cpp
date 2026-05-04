#include "Account.hpp"

Account::Account(int id, const std::string& owner, double balance)
    : id_(id), owner_(owner), balance_(balance) {}

void Account::deposit(double amount) {
    if (amount <= 0) throw std::invalid_argument("deposit amount positive");
    balance_ += amount;
}

void Account::withdraw(double amount) {
    if (amount <= 0) throw std::invalid_argument("withdraw amount positive");
    if (amount > balance_) throw std::runtime_error("insufficient funds");
    balance_ -= amount;
}

double Account::getBalance() const { return balance_; }
int Account::getId() const { return id_; }
std::string Account::getOwner() const { return owner_; }
