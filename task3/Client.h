#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Account.h"

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string passportNumber;
    std::string address;
    std::vector<std::shared_ptr<Account>> accounts;

public:
    Client(const std::string& fName, const std::string& lName,
           const std::string& passport = "", const std::string& addr = "")
        : firstName(fName), lastName(lName), passportNumber(passport), address(addr) {}

    // Getters
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getPassportNumber() const { return passportNumber; }
    std::string getAddress() const { return address; }
    const std::vector<std::shared_ptr<Account>>& getAccounts() const { return accounts; }

    // Account management
    void addAccount(std::shared_ptr<Account> account) {
        accounts.push_back(account);
    }

    std::shared_ptr<Account> findAccount(const std::string& accountId) const {
        for (const auto& account : accounts) {
            if (account->getAccountId() == accountId) {
                return account;
            }
        }
        return nullptr;
    }

    // Client information management
    void updatePassport(const std::string& newPassport) {
        passportNumber = newPassport;
    }

    void updateAddress(const std::string& newAddress) {
        address = newAddress;
    }

    // Validation
    bool isValid() const {
        return !firstName.empty() && !lastName.empty();
    }
};
