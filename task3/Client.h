#pragma once
#include <string>
#include <vector>
#include <memory>

class Account;

class Client {
private:
    std::string firstName;
    std::string lastName;
    std::string passportNumber;
    std::string address;
    std::vector<std::shared_ptr<Account>> accounts;

public:
    Client(const std::string& fName, const std::string& lName,
           const std::string& passport = "", const std::string& addr = "");

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPassportNumber() const;
    std::string getAddress() const;
    const std::vector<std::shared_ptr<Account>>& getAccounts() const;

    // Account management
    void addAccount(std::shared_ptr<Account> account);
    std::shared_ptr<Account> findAccount(const std::string& accountId) const;

    // Client information management
    void updatePassport(const std::string& newPassport);
    void updateAddress(const std::string& newAddress);

    // Validation
    bool isValid() const;
};
