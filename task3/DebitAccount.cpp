#include "DebitAccount.h"
#include "Client.h"

DebitAccount::DebitAccount(const std::string& id, std::shared_ptr<Client> client, double rate)
    : Account(id, client), interestRate(rate) {
}

void DebitAccount::deposit(double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid deposit amount");
    }
    balance += amount;
}

void DebitAccount::withdraw(double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid withdrawal amount");
    }
    if (amount > balance) {
        throw InsufficientFundsException("Not enough funds");
    }
    balance -= amount;
}

void DebitAccount::transfer(std::shared_ptr<Account> to, double amount) {
    if (isLocked) {
        throw AccountLockedException("Account is locked");
    }
    if (amount <= 0) {
        throw InvalidTransactionException("Invalid transfer amount");
    }
    if (amount > balance) {
        throw InsufficientFundsException("Not enough funds");
    }
    withdraw(amount);
    to->deposit(amount);
}

void DebitAccount::calculateInterest() {
    if (!isLocked) {
        balance += balance * interestRate;
    }
}

bool DebitAccount::canWithdraw(double amount) const {
    return !isLocked && amount > 0 && amount <= balance;
}

bool DebitAccount::canTransfer(double amount) const {
    return canWithdraw(amount);
}
