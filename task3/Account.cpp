#include "Account.h"
#include "Client.h"

Account::Account(const std::string& id, std::shared_ptr<Client> client)
    : accountId(id), balance(0.0), owner(client), isLocked(false) {
}

std::string Account::getAccountId() const {
    return accountId;
}

double Account::getBalance() const {
    return balance;
}

std::shared_ptr<Client> Account::getOwner() const {
    return owner.lock();
}

bool Account::getIsLocked() const {
    return isLocked;
}

void Account::lock() {
    isLocked = true;
}

void Account::unlock() {
    isLocked = false;
}
