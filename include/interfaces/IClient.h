#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IAccount.h"

// Interface for clients (Dependency Inversion Principle)
class IClient {
public:
    virtual ~IClient() = default;
    
    // Client identification
    virtual std::string GetId() const = 0;
    virtual std::string GetFirstName() const = 0;
    virtual std::string GetLastName() const = 0;
    virtual std::string GetFullName() const = 0;
    
    // Optional information
    virtual std::string GetPassportData() const = 0;
    virtual std::string GetAddress() const = 0;
    virtual void SetPassportData(const std::string& passportData) = 0;
    virtual void SetAddress(const std::string& address) = 0;
    
    // Account management
    virtual void AddAccount(std::shared_ptr<IAccount> account) = 0;
    virtual void RemoveAccount(const std::string& accountId) = 0;
    virtual std::shared_ptr<IAccount> GetAccount(const std::string& accountId) const = 0;
    virtual std::vector<std::shared_ptr<IAccount>> GetAllAccounts() const = 0;
    
    // Client information
    virtual std::string GetClientDetails() const = 0;
}; 