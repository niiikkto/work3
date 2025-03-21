#pragma once
#include "Account.h"

class CreditAccount : public Account {
private:
    double creditLimit;
    double commissionRate;

public:
    CreditAccount(const std::string& id, std::shared_ptr<Client> client,
                 double limit, double commission)
        : Account(id, client), creditLimit(limit), commissionRate(commission) {}

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
        if (amount > (balance + creditLimit)) {
            throw InsufficientFundsException("Exceeds credit limit");
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
        if (amount > (balance + creditLimit)) {
            throw InsufficientFundsException("Exceeds credit limit");
        }
        withdraw(amount);
        to->deposit(amount);
    }

    void calculateInterest() override {
        // Credit accounts don't earn interest
    }

    void calculateCommission() override {
        if (!isLocked && balance < 0) {
            double commission = std::abs(balance) * commissionRate;
            balance -= commission;
        }
    }

    bool canWithdraw(double amount) const override {
        return !isLocked && amount > 0 && amount <= (balance + creditLimit);
    }

    bool canTransfer(double amount) const override {
        return canWithdraw(amount);
    }

    double getCreditLimit() const { return creditLimit; }
    double getCommissionRate() const { return commissionRate; }
};
