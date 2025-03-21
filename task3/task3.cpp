// task3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>
#include "CentralBank.h"
#include "Bank.h"
#include "ConsoleUI.h"

int main() {
    try {
        // Create central bank
        auto centralBank = std::make_shared<CentralBank>("CB001");

        // Create some banks
        auto bank1 = std::make_shared<Bank>("B001", "First Bank");
        auto bank2 = std::make_shared<Bank>("B002", "Second Bank");
        auto bank3 = std::make_shared<Bank>("B003", "Third Bank");

        // Register banks with central bank
        centralBank->registerBank(bank1);
        centralBank->registerBank(bank2);
        centralBank->registerBank(bank3);

        // Create and run console UI
        ConsoleUI ui(centralBank);
        ui.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
