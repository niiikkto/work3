#pragma once
#include <string>
#include <stdexcept>

class BankingException : public std::runtime_error {
public:
    explicit BankingException(const std::string& message) 
        : std::runtime_error(message) {}
    
    virtual ~BankingException() = default;
};

class InsufficientFundsException : public BankingException {
public:
    explicit InsufficientFundsException(const std::string& message)
        : BankingException("Insufficient funds: " + message) {}
};

class InvalidTransactionException : public BankingException {
public:
    explicit InvalidTransactionException(const std::string& message)
        : BankingException("Invalid transaction: " + message) {}
};

class AccountLockedException : public BankingException {
public:
    explicit AccountLockedException(const std::string& message)
        : BankingException("Account locked: " + message) {}
};
