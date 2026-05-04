#include "Transaction.hpp"

bool Transaction::Make(Account& from, Account& to, int sum) {
    if (sum <= 0) return false;
    try {
        from.withdraw(sum);
        to.deposit(sum);
        return true;
    } catch (...) {
        return false;
    }
}
