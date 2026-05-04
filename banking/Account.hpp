#pragma once
#include <string>
#include <stdexcept>

class Account {
public:
    Account(int id, const std::string& owner, double balance = 0.0);
    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    virtual double getBalance() const;
    virtual int getId() const;
    virtual std::string getOwner() const;
private:
    int id_;
    std::string owner_;
    double balance_;
};
