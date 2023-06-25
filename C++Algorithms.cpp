// C++Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Algorithms.h"

void stringToInteger();


int main()
{
    char* input = (char*)malloc(sizeof(char) * 20);
    std::string menu = "Enter a command mentioned below to execute a home-made program\n\"cancel\" to exit the program\n\"atoi\" basically a string to integer";
    while (true)
    {
        std::cout << menu << "\n";
        std::cin >> input;
        if (!std::strcmp(input, "cancel"))
            break;
        if (!std::strcmp(input, "atoi"))
            stringToInteger();
    }
    free(input);
}

void stringToInteger()
{
    char* input = (char*)malloc(sizeof(char) * 1000);
    while (true)
    {
        std::cout << "Enter a number or type \"cancel\" to go back to the menu without memory leaks\n";
        _Notnull_ std::cin >> input;
        std::cout << "\n";
        if (!std::strcmp(input, "cancel"))
            break;
        try
        {
            std::string integerResult = std::to_string(Algorithms::atoi(input));
            std::cout << "Parsed number: " + integerResult + "\n";
        }
        catch (const std::string&)
        {
            std::cout << "Error while parsing the number";
        }
        std::cout << "\n\n";
    }
    free(input);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
