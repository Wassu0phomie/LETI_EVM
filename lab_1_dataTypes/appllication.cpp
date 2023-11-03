#pragma once
#include "application.h"
#include "dataTypes.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>


void TApplication::exec()
{
    char userChoice;
    setlocale(LC_ALL, "Russian");


    while (true) {
        system("cls");
        std::cout << "---------------------------------------" << '\n';
        std::cout << "Choose a category from below:" << '\n';
        std::cout <<
            "---------------------------------------\n"
            "0. Exit\n"
            "1.Double in memory\n"
            "2.Char in memory\n"
            "---------------------------------------\n"
            "\n>> ";

        std::cin >> userChoice;
        system("cls");

        switch (userChoice) {

        case '1':
        {
            std::cin.clear();
            double userInput;
            std::cout << "Еnter a number to get a binary representation for (double) " << '\n' << "\nInput: ";
            do
            {
                if (!std::cin)
                {
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                    std::cout << "\nIncorrect input. Enter new value: ";
                }
                std::cin >> userInput;
            } while (!std::cin);
            std::cout << "Output: ";
            std::string binaryDouble = getBitsOfDouble(userInput);
            std::cout << binaryDouble << '\n';



            while (true) {
                char choice;
                do {
                    std::cout << "\nInvert bytes? (y/n): ";
                    std::cin >> choice;
                } while (choice != 'y' && choice != 'n');

                if (choice == 'y') {
                    double value = userInput;
                    // Вводим номера бит
                    std::cout << "Enter the bit numbers you want to invert (separated by spaces \"e.g., 63...5 4 4 2 1 0\"): ";
                    std::cin.ignore(); // очищаем буфер после ввода числа
                    std::string positions;
                    std::getline(std::cin, positions);
                    std::string bits = getBitsOfDouble(value);
                    bits.erase(std::remove(bits.begin(), bits.end(), ' '), bits.end());
                    std::string invertedBits = invertDoubleBits(bits, positions);

                    std::cout << "Inverted bits: " << invertedBits << std::endl;
                    invertedBits.erase(std::remove(invertedBits.begin(), invertedBits.end(), ' '), invertedBits.end());
                    std::cout << "Inverted value: ";
                    fromBinaryToDouble(invertedBits);
                }
                else break;
            }

            break;
        }
        case '2':
        {
            char value;

            std::cout << "Еnter a number to get a binary representation for (char): ";
            if (!(std::cin >> value)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid" << '\n';
                break;
            }
            std::string binaryChar = getBitsOfChar(value);
            std::cout << binaryChar << '\n';

            char resultChar = value;
            while (true) {
                char choice;
                do {
                    std::cout << "\nInvert bytes? (y/n): ";
                    std::cin >> choice;
                } while (choice != 'y' && choice != 'n');

                if (choice == 'y') {
                    int numBits;
                    std::cout << "Enter the number of bits you want to invert: ";
                    std::cin >> numBits;

                    // Вводим номера бит
                    std::cout << "Enter the bit numbers you want to invert (separated by spaces): ";
                    std::cin.ignore(); // очищаем буфер после ввода числа
                    std::string indicesString;
                    std::getline(std::cin, indicesString);
                    std::istringstream iss(indicesString);
                    int index;
                    std::vector<int> bitIndices;
                    while (iss >> index) {
                        bitIndices.push_back(index);
                    }

                    // Проверяем, что количество введенных номеров битов соответствует указанному пользователем числу
                    if (bitIndices.size() != numBits || bitIndices.size() <= 0 || bitIndices.size() > 8) {
                        std::cout << "Invalid input. Incorrect number of bits!" << '\n';
                        break;
                    }

                    resultChar = invertCharBits(resultChar, bitIndices);
                    std::string resultBits = getBitsOfChar(resultChar);
                    std::cout << resultBits << '\n';
                }
                else break;
            }
            break;
        }
        case '0':
        {
            exit(0);
        }
        default:
        {
            std::cout << "Error\n";
            break;
        }
        }
        system("pause");

    }
}