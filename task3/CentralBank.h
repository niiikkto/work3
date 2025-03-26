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
    CentralBank(const std::string& id);

    // Bank management
    void registerBank(std::shared_ptr<Bank> bank);
    std::shared_ptr<Bank> findBank(const std::string& bankId) const;

    // Inter-bank operations
    void processInterBankTransfer(const std::string& fromBankId,
                                const std::string& toBankId,
                                const std::string& fromAccountId,
                                const std::string& toAccountId,
                                double amount);

    // System-wide operations
    void processInterestAndCommission();

    // Transaction rollback
    void rollbackTransaction(const std::string& bankId,
                           const std::string& transactionId);

    // Getters
    std::string getCentralBankId() const;
    const std::vector<std::shared_ptr<Bank>>& getBanks() const;
};
