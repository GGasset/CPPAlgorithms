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

		/*
			Parenthesis positions:
				bool*** (length = input_length)
					bool** (length = 2):
						bool* (length = 3):
							'(' at index 0, 1 if present, 0 otherwise
							'[' at index 1, 1 if present, 0 otherwise
							'{' at index 2, 1 if present, 0 otherwise

						bool* (length = 3): 
							')' at index 0, 1 if present, 0 otherwise
							']' at index 1, 1 if present, 0 otherwise
							'}' at index 2, 1 if present, 0 otherwise
		*/
		_Notnull_ bool*** parenthesisPositions = (bool***)malloc(sizeof(bool**) * input_length);
		if (!parenthesisPositions)
			throw std::exception("Not enough memory");

		for (size_t i = 0; i < input_length; i++)
		{
			parenthesisPositions[i] = (bool**)malloc(sizeof(bool*) * 2);
			if (!parenthesisPositions[i])
				throw new std::exception("Not enough memory");

			parenthesisPositions[i][0] = (bool*)malloc(sizeof(bool) * parenthesisTypesCount);
			parenthesisPositions[i][1] = (bool*)malloc(sizeof(bool) * parenthesisTypesCount);
			if (!parenthesisPositions[i][0] || !parenthesisPositions[i][1])
				throw std::exception("Not enough memory");
		}


		// Gather data
		char currentC;
		for (size_t i = 0; i < (currentC = input[i]) != '\000'; i++)
		{
			parenthesisPositions[i][0][0] = currentC == '(';
			parenthesisPositions[i][0][1] = currentC == '[';
			parenthesisPositions[i][0][2] = currentC == '{';

			parenthesisPositions[i][1][0] = currentC == ')';
			parenthesisPositions[i][1][1] = currentC == ']';
			parenthesisPositions[i][1][2] = currentC == '}';
		}

		// Process data
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
		for (size_t i = 0; i < input_length; i++)
		{
			free(parenthesisPositions[i][0]);
			free(parenthesisPositions[i][1]);
			free(parenthesisPositions[i]);
		}
		free(parenthesisPositions);

		return output;
	}
};

