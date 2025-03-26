#pragma once
#include <string>
#include <memory>
#include <chrono>
#include "Account.h"

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
};

enum class TransactionStatus {
    PENDING,
    COMPLETED,
    FAILED,
    CANCELLED
};

class Transaction {
private:
    std::string transactionId;
    TransactionType type;
    TransactionStatus status;
    double amount;
    std::shared_ptr<Account> fromAccount;
    std::shared_ptr<Account> toAccount;
    std::chrono::system_clock::time_point timestamp;
    bool isRollback;

public:
    Transaction(const std::string& id, TransactionType t, double amt,
                std::shared_ptr<Account> from, std::shared_ptr<Account> to = nullptr);

    // Getters
    std::string getTransactionId() const;
    TransactionType getType() const;
    TransactionStatus getStatus() const;
    double getAmount() const;
    std::shared_ptr<Account> getFromAccount() const;
    std::shared_ptr<Account> getToAccount() const;
    std::chrono::system_clock::time_point getTimestamp() const;
    bool getIsRollback() const;

    // Transaction execution
    virtual void execute();

    // Transaction rollback
    virtual void rollback();
};
