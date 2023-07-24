// C++Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Algorithms.h"

void stringToInteger();
void validParenthesis();
void changeBase10();
void toBase10();


int main()
{
    char* input = (char*)malloc(sizeof(char) * 100);
    std::string menu = "Enter a command mentioned below to execute a home-made program\n\"cancel\" to exit the program\n\"atoi\" basically a string to integer\n";
    menu += "\"valid_parenthesis\"\n";
    menu += "\"change_base\" changes from base 10 to any base\n";
    menu += "\"to base 10\" changes a number from any base to base 10\n";
    while (true)
    {

        std::cout << menu << "\n";
        std::cin.getline(input, sizeof(char) * 100);
        if (!std::strcmp(input, "cancel"))
            break;
        if (!std::strcmp(input, "atoi"))
            stringToInteger();
        if (!std::strcmp(input, "valid_parenthesis"))
            validParenthesis();
        if (!std::strcmp(input, "change_base"))
            changeBase10();
        if (!std::strcmp(input, "to base 10"))
            toBase10();
    }
    free(input);
}

void stringToInteger()
{
    char* input = (char*)malloc(sizeof(char) * 1000);
    while (true)
    {
        std::cout << "Enter a number or type \"cancel\" to go back to the menu without memory leaks\n";
        _Notnull_ std::cin.getline(input, sizeof(input));
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

void validParenthesis()
{
    char* input = (char*)malloc(sizeof(char) * 2000);
    while (true)
    {
        std::cout << "Enter a text to see whether it has valid parenthesis (2000 characters at max) or enter \"cancel\" to go back to the menu without memory leaks.\n";
        _Notnull_ std::cin.getline(input, sizeof(char) * 2000);
        std::cout << "\n";
        
        if (!std::strcmp(input, "cancel"))
            break;

        bool isValid = Algorithms::ValidParenthesis(input);
        std::cout << "Is the text valid regarding its parenthesis? " << isValid << "\n";
    }
    free(input);
}

void changeBase10()
{
    char* base10 = (char*)malloc(sizeof(char) * 200);
    char* newBase = (char*)malloc(sizeof(char) * 200);
    while (true)
    {
        try
        {
            std::cout << "Enter \"cancel\" at any moment to change the program\n";
            std::cout << "Enter the base 10 number: ";
            _Notnull_ std::cin.getline(base10, sizeof(char) * 200);
            std::cout << "\n";

            if (!std::strcmp(base10, "cancel"))
                break;

            std::cout << "Enter the new base: ";
            _Notnull_ std::cin.getline(newBase, sizeof(char) * 200);
            std::cout << "\n";

            if (!std::strcmp(base10, "cancel"))
                break;

            int base10_number = Algorithms::atoi(base10);
            int parsed_new_base = Algorithms::atoi(newBase);
            std::string new_number = Algorithms::changeBase(base10_number, parsed_new_base) + "\n";
            std::cout << new_number;
        }
        catch (const std::string*& err)
        {
            std::cout << err << "\n";
        }
    }

    free(base10);
    free(newBase);
}

void toBase10()
{
    char* number = (char*)malloc(sizeof(char) * 30);
    char* number_base = (char*)malloc(sizeof(char) * 30);
    while (true)
    {
        std::cout << "Enter \"cancel\" to change program at any time.\n";
        std::cout << "Enter a number in any base." << "\n" << "Number: ";
        std::cin.getline(number, sizeof(char) * 30);

        if (!std::strcmp(number, "cancel"))
            break;

        std::cout << "\n\n" << "Enter the base of the number you entered." << "\n" << "Base: ";
        std::cin.getline(number_base, sizeof(char) * 30);

        if (!std::strcmp(number_base, "cancel"))
            break;

        try
        {
            std::cout << "\n\n" << std::to_string(Algorithms::toBase10(number, Algorithms::atoi(number_base))) << "\n\n";
        }
        catch (const std::string& err)
        {
            std::cout << "\n\n" << err << "\n\n";
        }
    }
    free(number);
    free(number_base);
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
