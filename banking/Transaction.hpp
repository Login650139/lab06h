#pragma once
#include "Account.hpp"

class Transaction {
public:
    static bool Make(Account& from, Account& to, int sum);
};
