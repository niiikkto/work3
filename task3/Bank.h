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
    std::vector<std::shared_ptr<Transaction>> transactions;
    double creditLimit;
    double creditCommission;
    double debitInterestRate;
    std::unordered_map<double, double> depositInterestRates; // amount -> rate

public:
    Bank(const std::string& id, const std::string& bankName)
        : bankId(id), name(bankName), creditLimit(10000.0),
          creditCommission(0.01), debitInterestRate(0.01) {
        // Initialize deposit interest rates
        depositInterestRates[1000.0] = 0.02;
        depositInterestRates[5000.0] = 0.03;
        depositInterestRates[10000.0] = 0.04;
    }

    // Client management
    std::shared_ptr<Client> createClient(const std::string& firstName,
                                       const std::string& lastName,
                                       const std::string& passport = "",
                                       const std::string& address = "") {
        auto client = std::make_shared<Client>(firstName, lastName, passport, address);
        clients.push_back(client);
        return client;
    }

    std::shared_ptr<Client> findClient(const std::string& firstName,
                                     const std::string& lastName) const {
        for (const auto& client : clients) {
            if (client->getFirstName() == firstName && client->getLastName() == lastName) {
                return client;
            }
        }
        return nullptr;
    }

    // Account management
    std::shared_ptr<Account> createAccount(const std::string& accountType,
                                         std::shared_ptr<Client> client) {
        std::string accountId = generateAccountId();
        std::shared_ptr<Account> account;

        if (accountType == "debit") {
            account = std::make_shared<DebitAccount>(accountId, client, debitInterestRate);
        }
        else if (accountType == "credit") {
            account = std::make_shared<CreditAccount>(accountId, client, creditLimit, creditCommission);
        }
        else if (accountType == "deposit") {
            // Use default values for initial deposit and period
            account = std::make_shared<DepositAccount>(accountId, client, 1000.0, depositInterestRates[1000.0], 12);
        }
        else {
            throw InvalidTransactionException("Invalid account type");
        }

        accounts[accountId] = account;
        client->addAccount(account);
        return account;
    }

    std::shared_ptr<Account> findAccount(const std::string& accountId) const {
        auto it = accounts.find(accountId);
        return it != accounts.end() ? it->second : nullptr;
    }

    // Transaction management
    std::shared_ptr<Transaction> createTransaction(TransactionType type,
                                                 double amount,
                                                 std::shared_ptr<Account> from,
                                                 std::shared_ptr<Account> to = nullptr) {
        std::string transactionId = generateTransactionId();
        auto transaction = std::make_shared<Transaction>(transactionId, type, amount, from, to);
        transactions.push_back(transaction);
        return transaction;
    }

    void executeTransaction(std::shared_ptr<Transaction> transaction) {
        transaction->execute();
    }

    void rollbackTransaction(std::shared_ptr<Transaction> transaction) {
        transaction->rollback();
    }

    // Interest and commission calculations
    virtual void calculateInterestAndCommission() {
        for (const auto& account : accounts) {
            account.second->calculateInterest();
            account.second->calculateCommission();
        }
    }

    // Helper methods for account management
    void addAccount(std::shared_ptr<Account> account) {
        accounts[account->getAccountId()] = account;
    }

    double getDepositInterestRate(double amount) const {
        double rate = 0.02; // default rate
        for (const auto& pair : depositInterestRates) {
            if (amount >= pair.first) {
                rate = pair.second;
            }
        }
        return rate;
    }

    // Getters
    std::string getBankId() const { return bankId; }
    std::string getName() const { return name; }
    const std::vector<std::shared_ptr<Client>>& getClients() const { return clients; }
    const std::unordered_map<std::string, std::shared_ptr<Account>>& getAccounts() const { return accounts; }
    const std::vector<std::shared_ptr<Transaction>>& getTransactions() const { return transactions; }

    // Move generateAccountId to public section
    std::string generateAccountId() const {
        static int counter = 0;
        return bankId + "_ACC_" + std::to_string(++counter);
    }

protected:
    std::string generateTransactionId() const {
        static int counter = 0;
        return bankId + "_TRX_" + std::to_string(++counter);
    }
};
