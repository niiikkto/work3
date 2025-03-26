#pragma once
#include "Account.h"

class DebitAccount : public Account {
private:
    double interestRate;

public:
    DebitAccount(const std::string& id, std::shared_ptr<Client> client, double rate);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void transfer(std::shared_ptr<Account> to, double amount) override;
    void calculateInterest() override;
    bool canWithdraw(double amount) const override;
    bool canTransfer(double amount) const override;
};
