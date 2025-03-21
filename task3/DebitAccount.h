#pragma once
#include "Account.h"

class DebitAccount : public Account {
private:
    double interestRate;

public:
    DebitAccount(const std::string& id, std::shared_ptr<Client> client, double rate)
        : Account(id, client), interestRate(rate) {}

    void deposit(double amount) override {
        if (isLocked) {
            throw AccountLockedException("Account is locked");
        }
        if (amount <= 0) {
            throw InvalidTransactionException("Invalid deposit amount");
        }
        balance += amount;
    }

    void withdraw(double amount) override {
        if (isLocked) {
            throw AccountLockedException("Account is locked");
        }
        if (amount <= 0) {
            throw InvalidTransactionException("Invalid withdrawal amount");
        }
        if (amount > balance) {
            throw InsufficientFundsException("Not enough funds");
        }
        balance -= amount;
    }

    void transfer(std::shared_ptr<Account> to, double amount) override {
        if (isLocked) {
            throw AccountLockedException("Account is locked");
        }
        if (amount <= 0) {
            throw InvalidTransactionException("Invalid transfer amount");
        }
        if (amount > balance) {
            throw InsufficientFundsException("Not enough funds");
        }
        withdraw(amount);
        to->deposit(amount);
    }

    void calculateInterest() override {
        if (!isLocked) {
            balance += balance * interestRate;
        }
    }

    void calculateCommission() override {
        // Debit accounts don't have commission
    }

    bool canWithdraw(double amount) const override {
        return !isLocked && amount > 0 && amount <= balance;
    }

    bool canTransfer(double amount) const override {
        return canWithdraw(amount);
    }
};
