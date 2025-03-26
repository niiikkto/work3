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
                  double initial, double rate, int months);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void transfer(std::shared_ptr<Account> to, double amount) override;
    void calculateInterest() override;
    bool canWithdraw(double amount) const override;
    bool canTransfer(double amount) const override;

    std::chrono::system_clock::time_point getExpirationDate() const;
    double getInitialDeposit() const;
    double getInterestRate() const;
};
