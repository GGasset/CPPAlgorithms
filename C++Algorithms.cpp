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
void ReverseDemonstration();
void TwoSumDemonstration();
void LongestParenthesisSubtringDemonstration();

static void ParenthesisMenu()
{
    std::string description = "Algorithms regarding parenthesis\n";

    std::string entries = description + "Type \"cancel\" to exit this menu.\n\n";
    entries += "\"valid parenthesis\" to check if given strings have valid parenthesis\n";
    entries += "\"longest valid parenthesis\" in a input with just '(' and ')' will search for the longest valid substring. LeetCode difficulty: Hard\n";

    while (true)
    {
        std::cout << entries << std::endl;
        char* in = new char[150];
        std::cin.getline(in, 150);

        if (!strcmp(in, "cancel"))
        {
            delete[] in;
            return;
        }
        if (!strcmp(in, "valid parenthesis"))
            validParenthesis();
        if (!strcmp(in, "longest valid parenthesis"))
            LongestParenthesisSubtringDemonstration();
    }

}

int main()
{
    /*std::string presentation = "";
    presentation += "|                                 ?            ?                              \n";
    presentation += "|                               /  \\         // \\\\                           \n";
    presentation += "|                              /    \\       //   \\\\                          \n";
    presentation += "|                            ////####\\     //#####\\\\                         \n";
    presentation += "|                            ||||     \\###//                                 \n";
    presentation += "|                       _   *||||     ... ...                                \n";
    presentation += "|                   *        ||||      *   *                                 \n";
    presentation += "|                 *=|||      ||||      _______                               \n";
    presentation += "|               *==*|||      ||||     | ___  ))                               \n";
    presentation += "|-------------*==*--|||      ||||     |===| //---------------------------------                                \n";
    presentation += "|           *==*    |||      ||||          //                                 \n";
    presentation += "|           |==|    |||      ||||         //                                  \n";
    presentation += "|           |==|     \\\\\\     ||||        //                                 \n";
    presentation += "|           |==|      \\\\\\####++++#######//                                   \n";
    presentation += "|           |=/         |||  |||| ||__ ||__                                 \n";
    presentation += "|           |/         (___))|||| (___)(___)                                        \n";
    presentation += "|----------------------------||||--------------------------------------------\n";
    presentation += "|                            ||||                                       \n";
    presentation += "|                         ?---++--?                                     \n";
    presentation += "|                          \\     /                                     \n";
    presentation += "|                           \\   /                                      \n";
    presentation += "|                            \\ /                                       \n";
    presentation += "|                             ?\n";

    presentation += "                                                          Press Enter\n";
    std::cout << presentation << std::endl << std::endl;*/

    std::string presentation = "";
    presentation += "|                                                                         \n";
    presentation += "|                            ////####\\     //#####\\                         \n";
    presentation += "|                            ||||     \\###//                                  \n";
    presentation += "|                    _       ||||                                         \n";
    presentation += "|                   /#\\      ||||                                           \n";
    presentation += "|                 *=|||      ||||      _______                               \n";
    presentation += "|               *==*|||      ||||     | ___  ))                               \n";
    presentation += "|             *==*--|||      ||||     |===| //                                \n";
    presentation += "|           *==*    |||      ||||          //                                 \n";
    presentation += "|           |==|    |||      ||||         //                                  \n";
    presentation += "|           |==|     \\\\\\     ||||        //                                 \n";
    presentation += "|           |==|      \\\\\\####++++#######//                                   \n";
    presentation += "|           |=/              ||||                                        \n";
    presentation += "|                            ||||\n";
    presentation += "|                            ||||                                       \n";
    presentation += "|                         ?--++++-?                                     \n";
    presentation += "|                          \\     /                                     \n";
    presentation += "|                           \\   /                                      \n";
    presentation += "|                            \\ /                                       \n";
    presentation += "|                             ?\n";

    presentation += "                                                          Press Enter\n";
    std::cout << presentation << std::endl << std::endl;
    std::cin.get();

    char* input = (char*)malloc(sizeof(char) * 100);
    std::string menu = "Enter a command mentioned below to execute a home-made program\n\"cancel\" to exit the program\n\"atoi\" basically a string to integer\n";
    menu += "\"parenthesis\" for parenthesis related algorithms\n";
    menu += "\"change_base\" changes from base 10 to any base\n";
    menu += "\"to base 10\" changes a number from any base to base 10\n";
    menu += "\"reverse linked list\" to reverse a input list of numbers\n";
    menu += "\"hash table\" To use a data structure that stores key-value pairs\n";
    menu += "\"reverse inplace\" to reverse a fixed size integer array inplace (without creating a copy)\n";
    menu += "\"two sum\" to find two values that sum up to a target value\n";
    while (true)
    {
        try
        {
            std::cout << menu << std::endl;
            std::cin.getline(input, sizeof(char) * 100);
            if (!std::strcmp(input, "cancel"))
                break;
            if (!std::strcmp(input, "atoi"))
                stringToInteger();
            if (!std::strcmp(input, "parenthesis"))
                ParenthesisMenu();
            if (!std::strcmp(input, "change_base"))
                changeBase10();
            if (!std::strcmp(input, "to base 10"))
                toBase10();
            if (!std::strcmp(input, "reverse linked list"))
                ReverseLinkedList();
            if (!std::strcmp(input, "hash table"))
                HashTableDemonstration();
            if (!std::strcmp(input, "reverse inplace"))
                ReverseDemonstration();
            if (!std::strcmp(input, "two sum"))
                TwoSumDemonstration();
        }
        catch (const std::string& e)
        {
            std::cout << e << std::endl;
        }
    }
    free(input);
}

static DataStructures::SinglyLinkedListNode<int>* GetListInput(char* numbers, char separator = ' ')
{
    char currentC;
    DataStructures::SinglyLinkedListNode<int>* list = 0;
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
        free(number);
        if (!list)
        {
            list = new DataStructures::SinglyLinkedListNode<int>(parsedNumber);
            continue;
        }
        list->GetLastNode()->next = new DataStructures::SinglyLinkedListNode<int>(parsedNumber);
    }
    return list;
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

        DataStructures::SinglyLinkedListNode<int>* toReverse = GetListInput(numbers);

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

    std::cout << "\n\n" << "Type cancel at any moment to go back to main menu" << "\n";
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
    free(decision);
    free(key);
    free(value);
}

void ReverseDemonstration()
{
    char* input = new char[2000];
    
    while (true)
    {
        std::cout << std::endl << "Type \"cancel\" to exit this demonstration" << std::endl << "Enter a list of values separated by spaces" << std::endl << "Numbers: ";
        std::cin.getline(input, 2000);
        std::cout << std::endl;
        if (!strcmp(input, "cancel"))
            break;

        DataStructures::SinglyLinkedListNode<int>* parsed = GetListInput(input);
        size_t length = parsed->GetLength();
        int* output = parsed->ToArray();
        parsed->free();

        for (size_t i = 0; i < length; i++)
            std::cout << output[i] << " ";
        std::cout << std::endl;

        Algorithms::ReverseInplace(output, length);

        for (size_t i = 0; i < length; i++)
            std::cout << output[i] << " ";
        std::cout << std::endl;

        delete[] output;
    }
    
    delete[] input;
}

void TwoSumDemonstration()
{
    char input[2000]{""};
    while (true)
    {
        std::cout << std::endl << "Type \"cancel\" to exit to the menu" << std::endl << "Enter a target value: ";
        std::cin.getline(input, 2000);
        if (!strcmp(input, "cancel"))
            break;

        int target = Algorithms::atoi(input);
        
        std::cout << "Enter a list of values:" << std::endl;
        std::cin.getline(input, 2000);
        auto numbers = GetListInput(input);

        int* answer = Algorithms::TwoSum(numbers, target);
        if (!answer)
        {
            std::cout << "No numbers found that sum up to " << target << std::endl;
            continue;
        }

        int first_indice = answer[0];
        int second_indice = answer[1];

        //DataStructures::SinglyLinkedListNode<int>* current_node = ;
        int first_value = numbers->GetIndex(first_indice)->value;

        int second_value = numbers->GetIndex(second_indice)->value;

        std::cout << first_indice << " item (" << first_value << ") + " << second_indice << " item (" << second_value << ") = " << target << std::endl << std::endl;

        numbers->free();
    }
}

void LongestParenthesisSubtringDemonstration()
{
    char* in = new char[2000];
    while (true)
    {
        std::cout << "Enter a parenthesis string [only '(' or ')']" << std::endl << "String: ";
        std::cin.getline(in, 2000);
        if (!strcmp(in, "cancel"))
            break;

        std::string output = Algorithms::LongestValidParenthesisSubstring(in);
        if (!output.length())
        {
            std::cout << "No correct substring was found" << std::endl;
            continue;
        }

        std::cout << "Longest valid substring: " << output << std::endl << std::endl;
    }
    delete[] in;
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
