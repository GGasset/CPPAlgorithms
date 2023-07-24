#include <iostream>
#include <string>

#include "DataStructures.h"

#pragma once
static class Algorithms
{
public:
	static int atoi(char* input)
	{
		std::string formatException = "Format Exception";

		int output = 0;

		// Count not null characters
		int input_length = 0;
		for (int i = 0; input[i] != '\000'; i++, input_length++) {}


		char currentC;
		int digit_count = input_length;
		int sign_multiplier = 1;
		for (int i = 0; (currentC = input[i]) != '\000'; i++)
		{
			char currentC = input[i];

			if ((currentC > '9' || currentC < '0') && (currentC != '+' && currentC != '-'))
				throw formatException;

			if (i > 0 && (currentC == '+' || currentC == '-'))
				throw formatException;

			int is_sign = currentC == '+' || currentC == '-';

			// If the number is a negative sign store it for later processing
			int is_negative_sign = currentC == '-';
			sign_multiplier -= 2 * is_negative_sign;

			// If the current character is a sign no more processing is required
			if (is_sign)
				continue;

			// Process number to add it to output
			int unprocessed_number = currentC - '0';
			int processed_number = unprocessed_number * static_cast<int>(pow(10, digit_count - i - 1));
			output += processed_number;
		}

		output *= sign_multiplier;
		return output;
	}

	static bool ValidParenthesis(char* input)
	{
		size_t parenthesisTypesCount = 3;
		size_t input_length = 0;
		for (int i = 0; input[i] != '\000'; i++, input_length++) {  }

		// Process data
		char currentC;
		bool output = true;
		/*
			Queue for knowing which closing should go unless an new parenthesis opens.
		*/
		DataStructures::SingleLinkedListNode* closingQueue = new DataStructures::SingleLinkedListNode(0);

		for (size_t i = 0; i < (currentC = input[i]) != '\000'; i++)
		{
			if (currentC == '(' || currentC == '[' || currentC == '{')
			{
				DataStructures::SingleLinkedListNode* new_node = new DataStructures::SingleLinkedListNode((int)currentC);
				new_node->next = closingQueue;
				closingQueue = new_node;
			}
			if (currentC == ')' || currentC == ']' || currentC == '}')
			{
				char openingEquivalent = currentC - (2 * (currentC == ']' || currentC == '}')) - (currentC == ')');
				if (closingQueue[0].value == openingEquivalent)
				{
					closingQueue = closingQueue->next;
				}
				else
				{
					output = false;
					break;
				}
			}
		}

		output = output && closingQueue->value == 0;

		// Free memory
		auto previousNode = closingQueue;
		while (previousNode)
		{
			auto currentNode = previousNode->next;
			free(previousNode);
			previousNode = currentNode;
		}

		return output;
	}

	/// <summary>
	/// Changes base from base 10
	/// </summary>
	/// <param name="number"></param>
	/// <param name="base"></param>
	/// <returns></returns>
	static std::string changeBase(int number, int base)
	{
		if (base <= 0)
		{	
			throw std::string("bases less or equal than 0 aren't possible");
		}

		int current_division_output = number;
		DataStructures::SingleLinkedListNode *remainders = new DataStructures::SingleLinkedListNode(current_division_output % base);
		current_division_output /= base;
		int i = 1;
		while (current_division_output)
		{
			int remainder = current_division_output % base;
			remainders->GetLastNode()->next = new DataStructures::SingleLinkedListNode(remainder);
			current_division_output /= base;

			i++;
		};

		std::string output = std::string();

		DataStructures::SingleLinkedListNode* current_remainder = remainders;
		for (int j = 0; j < i; j++, current_remainder = current_remainder->next)
		{
			std::string digit = getNumberAsSingleDigit(current_remainder->value);
			output = digit + output;
		}
		
		remainders->free();
		return output;
	}


private:
	/// <summary>
	/// Returns a letter or a parenthesis with numbers and/or letters if the number is greater than 33 instead of a number greater than 9 for higher bases or else the number itself
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	static std::string getNumberAsSingleDigit(int number)
	{
		// +10 instead of +9 and + 1 due to 0 counting both on decimal base and on ASCII table
		int max_single_digit_number = 'z' - 'a' + 1 + 10;
		if (number > 9 && number < max_single_digit_number)
		{
			char* output = (char*)malloc(sizeof(char) * 2);
			if (output)
			{
				output[0] = (number - 9) + 'A' - 1;
				output[1] = '\000';
				std::string string_equivalent(output);
				free(output);
				return string_equivalent;
			}
			else
				throw std::string("Not enough memory");
		}
		if (number >= max_single_digit_number)
		{
			std::string output = "(";
			output += changeBase(number, max_single_digit_number) + ")";
			return output;
		}
		return std::to_string(number);
	}

public:
	static int toBase10(char* number, size_t number_base)
	{
		if (!ValidParenthesis(number))
		{
			std::cout << "Invalid parenthesis" << "\n";
			return -1;
		}
		if (number[0] == '\000')
		{
			std::cout << "Empty input" << "\n";
			return -1;
		}

		int input_length = 0;
		for (int i = 0; number[i] != '\000'; i++, input_length++) {  }
		
		int i = 0;
		bool is_negative = number[0] == '-';
		i += number[0] == '-';

		int output = 0;
		char currentC;
		while ((currentC = number[i]) != '\000')
		{
			char nextC = number[i + 1];

			// To lower
  			currentC += ('a' - 'A') * (currentC >= 'A' && currentC <= 'Z');
			nextC += ('a' - 'A') * (currentC >= 'A' && currentC <= 'Z');

			int i_multiplier = (static_cast<unsigned long long>(input_length) - i - 1);

			if (currentC == '(')
			{
				// Skip '('
				i++;

				// Recurse parenthesis contents toBase10 in base 'z' - 'a' + 10 + 1 and leave i after ')'
				size_t parenthesis_contents_length = 0;
				for (int j = i; number[j] != ')'; j++, parenthesis_contents_length++) {  }

				char* parenthesis_contents = (char*)malloc(sizeof(char) * (parenthesis_contents_length + 1));
				if (!parenthesis_contents)
					throw std::string("Not enough memory");
				for (size_t j = 0; (currentC = number[i]) != ')' && j < parenthesis_contents_length; j++, i++)
				{
					parenthesis_contents[j] = currentC;
				}
				parenthesis_contents[parenthesis_contents_length] = '\000';
				i++;

				output += toBase10(parenthesis_contents, 'z' - 'a' + 1 + 10);

				
				continue;
			}
			output += getSingleDigitAsNumber(currentC, number_base) * std::pow(number_base, i_multiplier);
			
			i++;
		}

		// Invert the number if necessary
		output *= -1 + 2 * !is_negative;
		return output;
	}

private:
	static int getSingleDigitAsNumber(char digit, size_t digit_base)
	{
		if (digit >= 'a' && digit <= 'z')
		{
			return digit - 'a' + 10;
		}
		else if (digit < '0' || digit > '9')
		{
			throw std::string("Format error");
		}

		// -1 due to ASCII table starting from 0
		return digit - '0';
	}
};

