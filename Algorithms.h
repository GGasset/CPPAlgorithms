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
			throw "bases less or equal than 0 arent possible";
		}
		if (base > 9)
		{
			throw "bases greater than base 9 aren't implemented";
		}

		int current_division_output = number;
		DataStructures::SingleLinkedListNode *remainders = new DataStructures::SingleLinkedListNode(current_division_output % base);
		current_division_output /= base;
		int i = 1;
		do
		{
			int remainder = current_division_output % base;
			remainders->GetLastNode()->next = new DataStructures::SingleLinkedListNode(remainder);
			current_division_output /= base;

			i++;
		} while (current_division_output);

		std::string output = std::string();

		DataStructures::SingleLinkedListNode* currentNode = remainders;
		for (int j = 0; j < i; j++, currentNode = currentNode->next)
		{
			output += getNumberAsSingleDigit(currentNode->value);
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
		return std::to_string(number);
	}

public:
};

