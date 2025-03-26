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
    Account(const std::string& id, std::shared_ptr<Client> client);
    virtual ~Account() = default;

    // Core account operations
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void transfer(std::shared_ptr<Account> to, double amount) = 0;
    
    // Interest and commission calculations
    virtual void calculateInterest() = 0;
    virtual void calculateCommission() { } // Пустая реализация по умолчанию
    
    // Getters
    std::string getAccountId() const;
    double getBalance() const;
    std::shared_ptr<Client> getOwner() const;
    bool getIsLocked() const;
    
    // State management
    virtual void lock();
    virtual void unlock();
    
    // Transaction management
    virtual bool canWithdraw(double amount) const = 0;
    virtual bool canTransfer(double amount) const = 0;
};
