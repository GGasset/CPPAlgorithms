// C++Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Algorithms.h"

void stringToInteger();
void validParenthesis();
void changeBase10();
void toBase10();
void ReverseLinkedList();
void HashTableDemonstration();


int main()
{
    char* input = (char*)malloc(sizeof(char) * 100);
    std::string menu = "Enter a command mentioned below to execute a home-made program\n\"cancel\" to exit the program\n\"atoi\" basically a string to integer\n";
    menu += "\"valid_parenthesis\"\n";
    menu += "\"change_base\" changes from base 10 to any base\n";
    menu += "\"to base 10\" changes a number from any base to base 10\n";
    menu += "\"reverse linked list\" to reverse a input list of numbers\n";
    menu += "\"hash table\" To use a data structure that stores key-value pairs";
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
        if (!std::strcmp(input, "reverse linked list"))
            ReverseLinkedList();
        if (!std::strcmp(input, "hash table"))
            HashTableDemonstration();
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

void ReverseLinkedList()
{
    char* numbers = (char*)malloc(sizeof(char) * 200);
    while (true)
    {
        std::cout << "Enter numbers separated by a space to reverse a singly linked list containing them. Type \"cancel\" to exit to the menu." << "\n" << "Numbers: ";
        std::cin.getline(numbers, sizeof(char) * 200);
        std::cout << "\n\n";

        if (!std::strcmp(numbers, "cancel"))
            break;

        char currentC;
        DataStructures::SinglyLinkedListNode<int>* toReverse = 0;
        for (size_t i = 0; (currentC = numbers[i]) != '\000'; i += 0)
        {
            i += currentC == ' ';

            size_t number_length = 0;
            for (size_t j = i; numbers[j] != ' ' && numbers[j] != '\000'; j++, number_length++) {}
            if (!number_length)
                continue;

            char* number = (char*)malloc(sizeof(char) * number_length + 1);
            if (!number)
                throw std::string("Not enough memory");

            for (size_t j = 0; j < number_length && numbers[i] != '\000' && numbers[i] != ' '; j++, i++)
            {
                currentC = numbers[i];
                number[j] = currentC;
            }
            number[number_length] = '\000';

            int parsedNumber = Algorithms::atoi(number);

            if (!toReverse)
            {
                toReverse = new DataStructures::SinglyLinkedListNode<int>(parsedNumber);
                continue;
            }
            toReverse->GetLastNode()->next = new DataStructures::SinglyLinkedListNode<int>(parsedNumber);
        }

        std::cout << toReverse->ToString() << "\n";
        
        DataStructures::SinglyLinkedListNode<int>* reversed = toReverse->Reverse();
        std::cout << reversed->ToString() << "\n";

        toReverse->free();
        reversed->free();

        std::cout << "\n";
    }
    free(numbers);
}

void HashTableDemonstration()
{
    DataStructures::HashTable<std::string> table = DataStructures::HashTable<std::string>(500);

    char* decision = (char*)malloc(sizeof(char) * 50);
    char* key = (char*)malloc(sizeof(char) * 50);
    char* value = (char*)malloc(sizeof(char) * 50);

    std::cout << "Type cancel at any moment to go back to main menu" << "\n";
    while (true)
    {
        std::cout << "Do you want to add a value or get a value?" << "\n" << "\"get\" or \"add\"? ";
        std::cin.getline(decision, sizeof(char) * 50);
        std::cout << "\n";
        if (!std::strcmp(decision, "cancel"))
            break;
        try
        {
            if (!strcmp(decision, "get"))
            {
                std::cout << "Enter the key (Must be an integer)" << "\n" << "Key: ";
                std::cin.getline(key, sizeof(char) * 50);
                std::cout << "\n";
                if (!std::strcmp(key, "cancel"))
                    break;


                bool is_found = false;
                std::string value = table.Get(Algorithms::atoi(key), is_found);
                
                std::cout << "Value: " << value << "\n\n";
            }
            else if (!strcmp(decision, "add"))
            {
                std::cout << "Enter a key (Must be an integer)" << "\n" << "Key: ";
                std::cin.getline(key, sizeof(char) * 50);
                std::cout << "\n";
                if (!std::strcmp(key, "cancel"))
                    break;


                std::cout << "Enter a value" << "\n" << "Value: ";
                std::cin.getline(value, sizeof(char) * 50);
                std::cout << "\n\n";
                if (!std::strcmp(value, "cancel"))
                    break;


                table.Add(Algorithms::atoi(key), std::string(value));
            }
            else
            {
                std::cout << "Invalid option" << "\n\n";
                continue;
            }
        }
        catch (const std::string& err)
        {
            std::cout << err << "\n\n";
        }
    }
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
