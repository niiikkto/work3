#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Bank.h"

class CentralBank {
private:
    std::string centralBankId;
    std::vector<std::shared_ptr<Bank>> banks;
    std::unordered_map<std::string, std::shared_ptr<Bank>> bankMap;

public:
    CentralBank(const std::string& id) : centralBankId(id) {}

    // Bank management
    void registerBank(std::shared_ptr<Bank> bank) {
        banks.push_back(bank);
        bankMap[bank->getBankId()] = bank;
    }

    std::shared_ptr<Bank> findBank(const std::string& bankId) const {
        auto it = bankMap.find(bankId);
        return it != bankMap.end() ? it->second : nullptr;
    }

    // Inter-bank operations
    void processInterBankTransfer(const std::string& fromBankId,
                                const std::string& toBankId,
                                const std::string& fromAccountId,
                                const std::string& toAccountId,
                                double amount) {
        auto fromBank = findBank(fromBankId);
        auto toBank = findBank(toBankId);

        if (!fromBank || !toBank) {
            throw InvalidTransactionException("One or both banks not found");
        }

        auto fromAccount = fromBank->findAccount(fromAccountId);
        auto toAccount = toBank->findAccount(toAccountId);

        if (!fromAccount || !toAccount) {
            throw InvalidTransactionException("One or both accounts not found");
        }

        // Create and execute transaction
        auto transaction = fromBank->createTransaction(
            TransactionType::TRANSFER, amount, fromAccount, toAccount);
        
        try {
            fromBank->executeTransaction(transaction);
        }
        catch (const BankingException&) {
            throw InvalidTransactionException("Failed to process inter-bank transfer");
        }
    }

    // System-wide operations
    void processInterestAndCommission() {
        for (const auto& bank : banks) {
            bank->calculateInterestAndCommission();
        }
    }

    // Transaction rollback
    void rollbackTransaction(const std::string& bankId,
                           const std::string& transactionId) {
        auto bank = findBank(bankId);
        if (!bank) {
            throw InvalidTransactionException("Bank not found");
        }

        // Find and rollback the transaction
        for (const auto& transaction : bank->getTransactions()) {
            if (transaction->getTransactionId() == transactionId) {
                bank->rollbackTransaction(transaction);
                return;
            }
        }

        throw InvalidTransactionException("Transaction not found");
    }

    // Getters
    std::string getCentralBankId() const { return centralBankId; }
    const std::vector<std::shared_ptr<Bank>>& getBanks() const { return banks; }
};
