#include "CentralBank.h"

CentralBank::CentralBank(const std::string& id) : centralBankId(id) {
}

void CentralBank::registerBank(std::shared_ptr<Bank> bank) {
    banks.push_back(bank);
    bankMap[bank->getBankId()] = bank;
}

std::shared_ptr<Bank> CentralBank::findBank(const std::string& bankId) const {
    auto it = bankMap.find(bankId);
    return it != bankMap.end() ? it->second : nullptr;
}

void CentralBank::processInterBankTransfer(const std::string& fromBankId,
                                         const std::string& toBankId,
                                         const std::string& fromAccountId,
                                         const std::string& toAccountId,
                                         double amount) {
    auto fromBank = findBank(fromBankId);
    auto toBank = findBank(toBankId);

    if (!fromBank || !toBank) {
        throw InvalidTransactionException("One or both banks not found");
    }

    auto fromAccount = fromBank->findAccount(fromAccountId);
    auto toAccount = toBank->findAccount(toAccountId);

    if (!fromAccount || !toAccount) {
        throw InvalidTransactionException("One or both accounts not found");
    }

    // Create and execute transaction
    auto transaction = fromBank->createTransaction(
        TransactionType::TRANSFER, amount, fromAccount, toAccount);
    
    try {
        fromBank->executeTransaction(transaction);
    }
    catch (const BankingException&) {
        throw InvalidTransactionException("Failed to process inter-bank transfer");
    }
}

void CentralBank::processInterestAndCommission() {
    for (const auto& bank : banks) {
        bank->calculateInterestAndCommission();
    }
}

void CentralBank::rollbackTransaction(const std::string& bankId,
                                   const std::string& transactionId) {
    auto bank = findBank(bankId);
    if (!bank) {
        throw InvalidTransactionException("Bank not found");
    }

    // Find and rollback the transaction
    for (const auto& transaction : bank->getTransactions()) {
        if (transaction->getTransactionId() == transactionId) {
            bank->rollbackTransaction(transaction);
            return;
        }
    }

    throw InvalidTransactionException("Transaction not found");
}

std::string CentralBank::getCentralBankId() const {
    return centralBankId;
}

const std::vector<std::shared_ptr<Bank>>& CentralBank::getBanks() const {
    return banks;
}
