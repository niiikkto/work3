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
                std::shared_ptr<Account> from, std::shared_ptr<Account> to = nullptr)
        : transactionId(id), type(t), status(TransactionStatus::PENDING),
          amount(amt), fromAccount(from), toAccount(to),
          timestamp(std::chrono::system_clock::now()), isRollback(false) {}

    // Getters
    std::string getTransactionId() const { return transactionId; }
    TransactionType getType() const { return type; }
    TransactionStatus getStatus() const { return status; }
    double getAmount() const { return amount; }
    std::shared_ptr<Account> getFromAccount() const { return fromAccount; }
    std::shared_ptr<Account> getToAccount() const { return toAccount; }
    std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }
    bool getIsRollback() const { return isRollback; }

    // Transaction execution
    virtual void execute() {
        if (status != TransactionStatus::PENDING) {
            throw InvalidTransactionException("Transaction is not in PENDING state");
        }

        try {
            switch (type) {
                case TransactionType::DEPOSIT:
                    fromAccount->deposit(amount);
                    break;
                case TransactionType::WITHDRAWAL:
                    fromAccount->withdraw(amount);
                    break;
                case TransactionType::TRANSFER:
                    if (!toAccount) {
                        throw InvalidTransactionException("Transfer requires destination account");
                    }
                    fromAccount->transfer(toAccount, amount);
                    break;
            }
            status = TransactionStatus::COMPLETED;
        }
        catch (const BankingException&) {
            status = TransactionStatus::FAILED;
            throw;
        }
    }

    // Transaction rollback
    virtual void rollback() {
        if (status != TransactionStatus::COMPLETED) {
            throw InvalidTransactionException("Can only rollback completed transactions");
        }

        try {
            switch (type) {
                case TransactionType::DEPOSIT:
                    fromAccount->withdraw(amount);
                    break;
                case TransactionType::WITHDRAWAL:
                    fromAccount->deposit(amount);
                    break;
                case TransactionType::TRANSFER:
                    if (!toAccount) {
                        throw InvalidTransactionException("Transfer requires destination account");
                    }
                    toAccount->transfer(fromAccount, amount);
                    break;
            }
            status = TransactionStatus::CANCELLED;
            isRollback = true;
        }
        catch (const BankingException&) {
            throw InvalidTransactionException("Failed to rollback transaction");
        }
    }
};
