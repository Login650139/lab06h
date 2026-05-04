#include <gtest/gtest.h>
#include "Account.hpp"

TEST(Account, ConstructorGetters) {
    Account a(1, "Alice", 100);
    EXPECT_EQ(a.getId(), 1);
    EXPECT_EQ(a.getOwner(), "Alice");
    EXPECT_DOUBLE_EQ(a.getBalance(), 100);
}

TEST(Account, Deposit) {
    Account a(2, "Bob", 50);
    a.deposit(25);
    EXPECT_DOUBLE_EQ(a.getBalance(), 75);
    EXPECT_THROW(a.deposit(-10), std::invalid_argument);
    EXPECT_THROW(a.deposit(0), std::invalid_argument);
}

TEST(Account, Withdraw) {
    Account a(3, "Charlie", 100);
    a.withdraw(30);
    EXPECT_DOUBLE_EQ(a.getBalance(), 70);
    EXPECT_THROW(a.withdraw(-5), std::invalid_argument);
    EXPECT_THROW(a.withdraw(0), std::invalid_argument);
    EXPECT_THROW(a.withdraw(200), std::runtime_error);
}
