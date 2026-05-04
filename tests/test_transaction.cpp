#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.hpp"
#include "mock_account.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

TEST(Transaction, MakeSuccess) {
    MockAccount from(1, "Dima", 100);
    MockAccount to(2, "Andrey", 50);
    EXPECT_CALL(from, withdraw(30)).Times(1);
    EXPECT_CALL(to, deposit(30)).Times(1);
    bool ok = Transaction::Make(from, to, 30);
    EXPECT_TRUE(ok);
}

TEST(Transaction, MakeFailWithdrawException) {
    MockAccount from(1, "Dima", 100);
    MockAccount to(2, "Andrey", 50);
    EXPECT_CALL(from, withdraw(200))
        .WillOnce(Throw(std::runtime_error("insufficient funds")));
    EXPECT_CALL(to, deposit(_)).Times(0);
    bool ok = Transaction::Make(from, to, 200);
    EXPECT_FALSE(ok);
}

TEST(Transaction, MakeInvalidAmount) {
    MockAccount from(1, "Dima", 100);
    MockAccount to(2, "Andrey", 50);
    EXPECT_CALL(from, withdraw(_)).Times(0);
    EXPECT_CALL(to, deposit(_)).Times(0);
    bool ok = Transaction::Make(from, to, -10);
    EXPECT_FALSE(ok);
    ok = Transaction::Make(from, to, 0);
    EXPECT_FALSE(ok);
}

TEST(Transaction, MakeDepositException) {
    MockAccount from(1, "Dima", 100);
    MockAccount to(2, "Andrey", 50);
    EXPECT_CALL(from, withdraw(30)).Times(1);
    EXPECT_CALL(to, deposit(30))
        .WillOnce(Throw(std::runtime_error("deposit failed")));
    bool ok = Transaction::Make(from, to, 30);
    EXPECT_FALSE(ok);
}
