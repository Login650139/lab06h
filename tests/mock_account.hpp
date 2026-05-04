#pragma once
#include "Account.hpp"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount(int id, const std::string& owner, double balance)
        : Account(id, owner, balance) {}
    MOCK_METHOD(void, deposit, (double amount), (override));
    MOCK_METHOD(void, withdraw, (double amount), (override));
    MOCK_METHOD(double, getBalance, (), (const, override));
    MOCK_METHOD(int, getId, (), (const, override));
    MOCK_METHOD(std::string, getOwner, (), (const, override));
};
