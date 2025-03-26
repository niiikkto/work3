#pragma once
#include "Account.h"

class CreditAccount : public Account {
private:
    double creditLimit;
    double commissionRate;

public:
    CreditAccount(const std::string& id, std::shared_ptr<Client> client,
                 double limit, double commission);

    void deposit(double amount) override;
    void withdraw(double amount) override;
    void transfer(std::shared_ptr<Account> to, double amount) override;
    void calculateInterest() override;
    void calculateCommission() override;
    bool canWithdraw(double amount) const override;
    bool canTransfer(double amount) const override;

    double getCreditLimit() const;
    double getCommissionRate() const;
};
