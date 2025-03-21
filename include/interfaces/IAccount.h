#pragma once
#include <string>

// Interface for all account types (Strategy Pattern)
class IAccount {
public:
    virtual ~IAccount() = default;
    
    // Core account operations
    virtual double GetBalance() const = 0;
    virtual std::string GetAccountId() const = 0;
    virtual bool Withdraw(double amount) = 0;
    virtual bool Deposit(double amount) = 0;
    virtual bool Transfer(IAccount& destination, double amount) = 0;
    
    // Time-based operations
    virtual void DailyUpdate() = 0;
    virtual void MonthlyUpdate() = 0;
    
    // Account information
    virtual std::string GetAccountType() const = 0;
    virtual std::string GetAccountDetails() const = 0;
}; 