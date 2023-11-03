#include "dataTypes.h"
#include <vector>


std::string getBitsOfChar(char signedChar) {

    std::string CharInBin;

    std::cout << "\nChar: " << signedChar << "\nASCII code (" << static_cast<int>(signedChar) << ")\n"; // Выводим знаковое значение
    std::cout << "Char in memory: ";

    for (int i = 7; i >= 0; --i) {
        char mask = 1 << i;
        char bit = (signedChar & mask) ? '1' : '0';

        CharInBin += bit;
    }
    return CharInBin;

}


std::string getBitsOfDouble(double value) {
    std::string DoubleInBin;

    union DoubleAsBytes
    {
        double data;
        int arr[2];
    };

    DoubleAsBytes unionData;
    unionData.data = value;

    int  count = 2;

    int mask = 1 << (sizeof(int) * 8 - 1);

    for (int i = 1; i >= 0; i--)
    {
        for (int j = 0; j < sizeof(float) * 8; j++)
        {
            if ((i == 1 && j == 1) || (j == 12 && i == 1))
            {
                DoubleInBin += ' ';
            }

            char bit = unionData.arr[i] & mask ? '1' : '0';
            DoubleInBin += bit;
            mask = 1 << (sizeof(float) * 16 - count);
            count++;
        }
    }
    return DoubleInBin;

}



char invertCharBits(char signedChar, const std::vector<int>& bitIndices) {
    for (int bitIndex : bitIndices) {
        if (bitIndex >= 0 && bitIndex < 8) {
            char mask = 1 << bitIndex;
            signedChar ^= mask; // Инвертируем бит
        }
    }
    return signedChar;
}


std::string invertDoubleBits(std::string bits, const std::string& positions) {

    std::istringstream iss(positions); // Создаем поток для разделения строк
    int index;
    int length = bits.size();

    while (iss >> index) {
        if (index >= 0 && index < bits.size()) {
            if (bits[length - 1 - index] == '0') {
                bits[length - 1 - index] = '1';
            }
            else {
                bits[length - 1 - index] = '0';
            }
        }
    }
    // Вставляем пробелы для разделения знакового разряда и порядка
    bits.insert(length - 63, " ");
    bits.insert(length - 51, " ");

    return bits;
}

void fromBinaryToDouble(std::string DoubleInBin)
{
    union {
        double newDouble;
        long long value = 0;
    };
    unsigned order = sizeof(double) * 8;
    unsigned long long mask = 0; // Инициализация переменной mask значением 0

    for (size_t i = 0; i < order; i++) {
        if (DoubleInBin[i] == '1') {
            mask = 1ULL << (order - 1 - i);
        }
        else {
            mask = 0; // Присваивание переменной mask значения 0
        }
        value |= mask;
    }

    std::cout << newDouble << std::endl;
}

