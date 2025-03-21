#pragma once
#include <string>
#include <memory>
#include "BankingException.h"

class Client;

class Account {
protected:
    std::string accountId;
    double balance;
    std::weak_ptr<Client> owner;
    bool isLocked;

public:
    Account(const std::string& id, std::shared_ptr<Client> client)
        : accountId(id), balance(0.0), owner(client), isLocked(false) {}
    
    virtual ~Account() = default;

    // Core account operations
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void transfer(std::shared_ptr<Account> to, double amount) = 0;
    
    // Interest and commission calculations
    virtual void calculateInterest() = 0;
    virtual void calculateCommission() = 0;
    
    // Getters
    std::string getAccountId() const { return accountId; }
    double getBalance() const { return balance; }
    std::shared_ptr<Client> getOwner() const { return owner.lock(); }
    bool getIsLocked() const { return isLocked; }
    
    // State management
    virtual void lock() { isLocked = true; }
    virtual void unlock() { isLocked = false; }
    
    // Transaction management
    virtual bool canWithdraw(double amount) const = 0;
    virtual bool canTransfer(double amount) const = 0;
};
