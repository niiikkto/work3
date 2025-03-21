#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "CentralBank.h"
#include "Bank.h"
#include "Client.h"
#include "Account.h"
#include "DebitAccount.h"
#include "CreditAccount.h"
#include "DepositAccount.h"

class ConsoleUI {
private:
    std::shared_ptr<CentralBank> centralBank;
    std::shared_ptr<Bank> currentBank;
    std::shared_ptr<Client> currentClient;

    void displayMainMenu() {
        std::cout << "\n=== Banking System Menu ===\n"
                  << "1. Select Bank\n"
                  << "2. Create Client\n"
                  << "3. Create Account\n"
                  << "4. Perform Transaction\n"
                  << "5. View Account Balance\n"
                  << "6. View Transaction History\n"
                  << "7. Rollback Transaction\n"
                  << "8. Exit\n"
                  << "Choice: ";
    }

    void selectBank() {
        std::cout << "\nAvailable Banks:\n";
        for (const auto& bank : centralBank->getBanks()) {
            std::cout << bank->getBankId() << " - " << bank->getName() << "\n";
        }
        std::cout << "Enter Bank ID: ";
        std::string bankId;
        std::getline(std::cin, bankId);
        
        currentBank = centralBank->findBank(bankId);
        if (!currentBank) {
            std::cout << "Bank not found!\n";
        } else {
            std::cout << "Selected bank: " << currentBank->getName() << "\n";
        }
    }

    void createClient() {
        if (!currentBank) {
            std::cout << "Please select a bank first!\n";
            return;
        }

        std::string firstName, lastName, passport, address;
        std::cout << "Enter First Name: ";
        std::getline(std::cin, firstName);
        std::cout << "Enter Last Name: ";
        std::getline(std::cin, lastName);
        std::cout << "Enter Passport Number (optional): ";
        std::getline(std::cin, passport);
        std::cout << "Enter Address (optional): ";
        std::getline(std::cin, address);

        currentClient = currentBank->createClient(firstName, lastName, passport, address);
        std::cout << "Client created successfully!\n";
    }

    void createAccount() {
        if (!currentBank || !currentClient) {
            std::cout << "Please select a bank and create a client first!\n";
            return;
        }

        std::cout << "\nAccount Types:\n"
                  << "1. Debit Account\n"
                  << "2. Credit Account\n"
                  << "3. Deposit Account\n"
                  << "Choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        try {
            std::shared_ptr<Account> account;
            switch (choice) {
                case 1:
                    account = currentBank->createAccount("debit", currentClient);
                    break;
                case 2:
                    account = currentBank->createAccount("credit", currentClient);
                    break;
                case 3: {
                    double initialDeposit;
                    int months;
                    std::cout << "Enter initial deposit amount: ";
                    std::cin >> initialDeposit;
                    std::cout << "Enter deposit period (months): ";
                    std::cin >> months;
                    std::cin.ignore();

                    std::string accountId = currentBank->generateAccountId();
                    account = std::make_shared<DepositAccount>(accountId, currentClient, 
                                                             initialDeposit, 
                                                             currentBank->getDepositInterestRate(initialDeposit),
                                                             months);
                    currentBank->addAccount(account);
                    currentClient->addAccount(account);
                    break;
                }
                default:
                    std::cout << "Invalid choice!\n";
                    return;
            }
            std::cout << "Account created successfully! Account ID: " << account->getAccountId() << "\n";
        }
        catch (const BankingException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    void performTransaction() {
        if (!currentBank || !currentClient) {
            std::cout << "Please select a bank and create a client first!\n";
            return;
        }

        std::cout << "\nTransaction Types:\n"
                  << "1. Deposit\n"
                  << "2. Withdraw\n"
                  << "3. Transfer\n"
                  << "Choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        try {
            std::string accountId;
            double amount;
            std::cout << "Enter Account ID: ";
            std::getline(std::cin, accountId);
            std::cout << "Enter Amount: ";
            std::cin >> amount;
            std::cin.ignore();

            auto account = currentBank->findAccount(accountId);
            if (!account) {
                std::cout << "Account not found!\n";
                return;
            }

            auto transaction = currentBank->createTransaction(
                static_cast<TransactionType>(choice - 1), amount, account);
            currentBank->executeTransaction(transaction);
            std::cout << "Transaction completed successfully!\n";
        }
        catch (const BankingException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    void viewBalance() {
        if (!currentBank || !currentClient) {
            std::cout << "Please select a bank and create a client first!\n";
            return;
        }

        std::cout << "\nYour Accounts:\n";
        for (const auto& account : currentClient->getAccounts()) {
            std::cout << "Account ID: " << account->getAccountId()
                      << " Balance: " << account->getBalance() << "\n";
        }
    }

    void viewTransactionHistory() {
        if (!currentBank) {
            std::cout << "Please select a bank first!\n";
            return;
        }

        std::cout << "\nTransaction History:\n";
        for (const auto& transaction : currentBank->getTransactions()) {
            std::cout << "ID: " << transaction->getTransactionId()
                      << " Type: " << static_cast<int>(transaction->getType())
                      << " Amount: " << transaction->getAmount()
                      << " Status: " << static_cast<int>(transaction->getStatus()) << "\n";
        }
    }

    void rollbackTransaction() {
        if (!currentBank) {
            std::cout << "Please select a bank first!\n";
            return;
        }

        std::string transactionId;
        std::cout << "Enter Transaction ID to rollback: ";
        std::getline(std::cin, transactionId);

        try {
            centralBank->rollbackTransaction(currentBank->getBankId(), transactionId);
            std::cout << "Transaction rolled back successfully!\n";
        }
        catch (const BankingException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

public:
    ConsoleUI(std::shared_ptr<CentralBank> cb) : centralBank(cb) {}

    void run() {
        int choice;
        do {
            displayMainMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1:
                    selectBank();
                    break;
                case 2:
                    createClient();
                    break;
                case 3:
                    createAccount();
                    break;
                case 4:
                    performTransaction();
                    break;
                case 5:
                    viewBalance();
                    break;
                case 6:
                    viewTransactionHistory();
                    break;
                case 7:
                    rollbackTransaction();
                    break;
                case 8:
                    std::cout << "Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice!\n";
            }
        } while (choice != 8);
    }
};
