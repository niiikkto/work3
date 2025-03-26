#include "DepositAccount.h"
#include "Client.h"

DepositAccount::DepositAccount(const std::string& id, std::shared_ptr<Client> client,
                               double initial, double rate, int months)
    : Account(id, client), initialDeposit(initial), interestRate(rate) {
    auto now = std::chrono::system_clock::now();
    expirationDate = now + std::chrono::hours(24 * 30 * months);
    balance = initial;
}

void DepositAccount::deposit(double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid deposit amount");
    }
    balance += amount;
}

void DepositAccount::withdraw(double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid withdrawal amount");
    }
    if (amount > balance) {
        throw InsufficientFundsException("Not enough funds");
    }
    if (std::chrono::system_clock::now() < expirationDate) {
        throw AccountLockedException("Deposit period not expired");
    }
    balance -= amount;
}

void DepositAccount::transfer(std::shared_ptr<Account> to, double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid transfer amount");
    }
    if (amount > balance) {
        throw InsufficientFundsException("Not enough funds");
    }
    if (std::chrono::system_clock::now() < expirationDate) {
        throw AccountLockedException("Deposit period not expired");
    }
    withdraw(amount);
    to->deposit(amount);
}

void DepositAccount::calculateInterest() {
    if (!isLocked) {
        balance += balance * interestRate;
    }
}

bool DepositAccount::canWithdraw(double amount) const {
    return !isLocked && amount > 0 && amount <= balance &&
           std::chrono::system_clock::now() >= expirationDate;
}

bool DepositAccount::canTransfer(double amount) const {
    return canWithdraw(amount);
}

std::chrono::system_clock::time_point DepositAccount::getExpirationDate() const {
    return expirationDate;
}

double DepositAccount::getInitialDeposit() const {
    return initialDeposit;
}

double DepositAccount::getInterestRate() const {
    return interestRate;
}
