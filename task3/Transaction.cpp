#include "Transaction.h"
#include "Client.h"

Transaction::Transaction(const std::string& id, TransactionType t, double amt,
                         std::shared_ptr<Account> from, std::shared_ptr<Account> to)
    : transactionId(id), type(t), status(TransactionStatus::PENDING),
      amount(amt), fromAccount(from), toAccount(to),
      timestamp(std::chrono::system_clock::now()), isRollback(false) {
}

std::string Transaction::getTransactionId() const {
    return transactionId;
}

TransactionType Transaction::getType() const {
    return type;
}

TransactionStatus Transaction::getStatus() const {
    return status;
}

double Transaction::getAmount() const {
    return amount;
}

std::shared_ptr<Account> Transaction::getFromAccount() const {
    return fromAccount;
}

std::shared_ptr<Account> Transaction::getToAccount() const {
    return toAccount;
}

std::chrono::system_clock::time_point Transaction::getTimestamp() const {
    return timestamp;
}

bool Transaction::getIsRollback() const {
    return isRollback;
}

void Transaction::execute() {
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

void Transaction::rollback() {
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
