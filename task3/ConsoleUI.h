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

    void displayMainMenu();
    void selectBank();
    void createClient();
    void createAccount();
    void performTransaction();
    void viewBalance();
    void viewTransactionHistory();
    void rollbackTransaction();

public:
    ConsoleUI(std::shared_ptr<CentralBank> cb);
    void run();
};
