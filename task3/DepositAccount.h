#pragma once
#include "Account.h"
#include <chrono>

class DepositAccount : public Account {
private:
    std::chrono::system_clock::time_point expirationDate;
    double initialDeposit;
    double interestRate;

public:
    DepositAccount(const std::string& id, std::shared_ptr<Client> client,
                  double initial, double rate, int months)
        : Account(id, client), initialDeposit(initial), interestRate(rate) {
        auto now = std::chrono::system_clock::now();
        expirationDate = now + std::chrono::hours(24 * 30 * months);
        balance = initial;
    }

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
        if (std::chrono::system_clock::now() < expirationDate) {
            throw AccountLockedException("Deposit period not expired");
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
        if (std::chrono::system_clock::now() < expirationDate) {
            throw AccountLockedException("Deposit period not expired");
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
        // Deposit accounts don't have commission
    }

    bool canWithdraw(double amount) const override {
        return !isLocked && amount > 0 && amount <= balance &&
               std::chrono::system_clock::now() >= expirationDate;
    }

    bool canTransfer(double amount) const override {
        return canWithdraw(amount);
    }

    std::chrono::system_clock::time_point getExpirationDate() const {
        return expirationDate;
    }

    double getInitialDeposit() const { return initialDeposit; }
    double getInterestRate() const { return interestRate; }
};
