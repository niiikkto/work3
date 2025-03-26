#include "Client.h"
#include "Account.h"

Client::Client(const std::string& fName, const std::string& lName,
           const std::string& passport, const std::string& addr)
    : firstName(fName), lastName(lName), passportNumber(passport), address(addr) {
}

std::string Client::getFirstName() const {
    return firstName;
}

std::string Client::getLastName() const {
    return lastName;
}

std::string Client::getPassportNumber() const {
    return passportNumber;
}

std::string Client::getAddress() const {
    return address;
}

const std::vector<std::shared_ptr<Account>>& Client::getAccounts() const {
    return accounts;
}

void Client::addAccount(std::shared_ptr<Account> account) {
    accounts.push_back(account);
}

std::shared_ptr<Account> Client::findAccount(const std::string& accountId) const {
    for (const auto& account : accounts) {
        if (account->getAccountId() == accountId) {
            return account;
        }
    }
    return nullptr;
}

void Client::updatePassport(const std::string& newPassport) {
    passportNumber = newPassport;
}

void Client::updateAddress(const std::string& newAddress) {
    address = newAddress;
}

bool Client::isValid() const {
    return !firstName.empty() && !lastName.empty();
}
