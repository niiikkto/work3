#include "CreditAccount.h"
#include "Client.h"
#include <cmath>

CreditAccount::CreditAccount(const std::string& id, std::shared_ptr<Client> client,
                           double limit, double commission)
    : Account(id, client), creditLimit(limit), commissionRate(commission) {
}

void CreditAccount::deposit(double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid deposit amount");
    }
    balance += amount;
}

void CreditAccount::withdraw(double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid withdrawal amount");
    }
    if (amount > (balance + creditLimit)) {
        throw InsufficientFundsException("Exceeds credit limit");
    }
    balance -= amount;
}

void CreditAccount::transfer(std::shared_ptr<Account> to, double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid transfer amount");
    }
    if (amount > (balance + creditLimit)) {
        throw InsufficientFundsException("Exceeds credit limit");
    }
    withdraw(amount);
    to->deposit(amount);
}

void CreditAccount::calculateInterest() {
    // Credit accounts don't earn interest
}

void CreditAccount::calculateCommission() {
    if (!isLocked && balance < 0) {
        double commission = std::abs(balance) * commissionRate;
        balance -= commission;
    }
}

bool CreditAccount::canWithdraw(double amount) const {
    return !isLocked && amount > 0 && amount <= (balance + creditLimit);
}

bool CreditAccount::canTransfer(double amount) const {
    return canWithdraw(amount);
}

double CreditAccount::getCreditLimit() const {
    return creditLimit;
}

double CreditAccount::getCommissionRate() const {
    return commissionRate;
}
