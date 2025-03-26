#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Client.h"
#include "Account.h"
#include "Transaction.h"
#include "DebitAccount.h"
#include "CreditAccount.h"
#include "DepositAccount.h"

class Bank {
protected:
    std::string bankId;
    std::string name;
    std::vector<std::shared_ptr<Client>> clients;
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts;
    std::vector<std::shared_ptr<Transaction>> transactions; // transactions history хранится история всех транзакций, выполненных через данный банк.
    double creditLimit;
    double creditCommission;
    double debitInterestRate;
    std::unordered_map<double, double> depositInterestRates; // — это хеш-таблица, которая связывает суммы вкладов с соответствующими процентными ставками для депозитных счетов.

public:
    Bank(const std::string& id, const std::string& bankName);

    // Client management
    std::shared_ptr<Client> createClient(const std::string& firstName,
                                       const std::string& lastName,
                                       const std::string& passport = "",
                                       const std::string& address = "");

    std::shared_ptr<Client> findClient(const std::string& firstName,
                                     const std::string& lastName) const;

    // Account management
    std::shared_ptr<Account> createAccount(const std::string& accountType,
                                         std::shared_ptr<Client> client);

    std::shared_ptr<Account> findAccount(const std::string& accountId) const;

    // Transaction management
    std::shared_ptr<Transaction> createTransaction(TransactionType type,
                                                 double amount,
                                                 std::shared_ptr<Account> from,
                                                 std::shared_ptr<Account> to = nullptr);

    void executeTransaction(std::shared_ptr<Transaction> transaction);
    void rollbackTransaction(std::shared_ptr<Transaction> transaction);

    // Interest and commission calculations
    virtual void calculateInterestAndCommission();

    // Helper methods for account management
    void addAccount(std::shared_ptr<Account> account);
    double getDepositInterestRate(double amount) const;

    // Getters
    std::string getBankId() const;
    std::string getName() const;
    const std::vector<std::shared_ptr<Client>>& getClients() const;
    const std::unordered_map<std::string, std::shared_ptr<Account>>& getAccounts() const;
    const std::vector<std::shared_ptr<Transaction>>& getTransactions() const;

    // ID generation
    std::string generateAccountId() const;

protected:
    std::string generateTransactionId() const;
};
