#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IClient.h"
#include "IAccount.h"

// Forward declaration of Transaction class
class Transaction;

// Interface for banks (Dependency Inversion Principle)
class IBank {
public:
    virtual ~IBank() = default;
    
    // Bank identification
    virtual std::string GetId() const = 0;
    virtual std::string GetName() const = 0;
    
    // Client management
    virtual void RegisterClient(std::shared_ptr<IClient> client) = 0;
    virtual void RemoveClient(const std::string& clientId) = 0;
    virtual std::shared_ptr<IClient> GetClient(const std::string& clientId) const = 0;
    virtual std::vector<std::shared_ptr<IClient>> GetAllClients() const = 0;
    
    // Account management
    virtual std::shared_ptr<IAccount> CreateDebitAccount(const std::string& clientId, double initialDeposit) = 0;
    virtual std::shared_ptr<IAccount> CreateDepositAccount(const std::string& clientId, double initialDeposit, int termInMonths) = 0;
    virtual std::shared_ptr<IAccount> CreateCreditAccount(const std::string& clientId, double initialDeposit, double creditLimit) = 0;
    virtual void CloseAccount(const std::string& accountId) = 0;
    virtual std::shared_ptr<IAccount> GetAccount(const std::string& accountId) const = 0;
    virtual std::vector<std::shared_ptr<IAccount>> GetAllAccounts() const = 0;
    virtual std::vector<std::shared_ptr<IAccount>> GetClientAccounts(const std::string& clientId) const = 0;
    
    // Transaction management
    virtual bool ProcessWithdrawal(const std::string& accountId, double amount) = 0;
    virtual bool ProcessDeposit(const std::string& accountId, double amount) = 0;
    virtual bool ProcessTransfer(const std::string& sourceAccountId, const std::string& destinationAccountId, double amount) = 0;
    virtual bool CancelTransaction(const std::string& transactionId) = 0;
    virtual std::vector<std::shared_ptr<Transaction>> GetAccountTransactions(const std::string& accountId) const = 0;
    
    // Time-based operations
    virtual void ProcessDailyUpdates() = 0;
    virtual void ProcessMonthlyUpdates() = 0;
    
    // Bank information
    virtual std::string GetBankDetails() const = 0;
    
    // Interest rates and fees
    virtual double GetDebitInterestRate() const = 0;
    virtual double GetDepositInterestRate(double amount) const = 0;
    virtual double GetCreditLimit() const = 0;
    virtual double GetCreditCommission() const = 0;
    
    // Update bank parameters
    virtual void SetDebitInterestRate(double rate) = 0;
    virtual void SetCreditCommission(double commission) = 0;
    virtual void SetCreditLimit(double limit) = 0;
}; 