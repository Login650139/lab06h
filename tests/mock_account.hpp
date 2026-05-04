#pragma once
#include "Account.hpp"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount(int id, const std::string& owner, double balance)
        : Account(id, owner, balance) {}
    MOCK_METHOD1(deposit, void(double));
    MOCK_METHOD1(withdraw, void(double));
    MOCK_CONST_METHOD0(getBalance, double());
    MOCK_CONST_METHOD0(getId, int());
    MOCK_CONST_METHOD0(getOwner, std::string());
};
