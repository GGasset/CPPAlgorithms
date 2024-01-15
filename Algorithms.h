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
		DataStructures::SinglyLinkedListNode<int>* closingQueue = new DataStructures::SinglyLinkedListNode<int>(0);

		for (size_t i = 0; i < (currentC = input[i]) != '\000'; i++)
		{
			if (currentC == '(' || currentC == '[' || currentC == '{')
			{
				DataStructures::SinglyLinkedListNode<int>* new_node = new DataStructures::SinglyLinkedListNode<int>((int)currentC);
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
		DataStructures::SinglyLinkedListNode<int>*remainders = new DataStructures::SinglyLinkedListNode<int>(current_division_output % base);
		current_division_output /= base;
		int i = 1;
		while (current_division_output)
		{
			int remainder = current_division_output % base;
			remainders->GetLastNode()->next = new DataStructures::SinglyLinkedListNode<int>(remainder);
			current_division_output /= base;

			i++;
		};

		std::string output = std::string();

		DataStructures::SinglyLinkedListNode<int>* current_remainder = remainders;
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

				int parenthesis_output = toBase10(parenthesis_contents, 'z' - 'a' + 1 + 10);
				if (parenthesis_output >= number_base)
					throw std::string("Digit higher than base.");

				output += parenthesis_output;

				
				continue;
			}

			int not_powered_number = getSingleDigitAsNumber(currentC, number_base);
			int digit_as_base_10 = not_powered_number * std::pow(number_base, i_multiplier);
			if (not_powered_number >= number_base)
				throw std::string("Digit higher than base.");

			output += digit_as_base_10;
			
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

public:
	/*static double divide(int dividend, int quotient, short division_guess = 2, bool calculate_decimal = false, int decimal_digit_count = 5)
	{
		if (!dividend)
			return 0;

		if (!quotient)
			throw std::string("You just tried to divide by 0, I mean... duhhh");

		if (quotient < 10 && quotient > -10)
			return dividend / quotient;

		if (division_guess < 2 || division_guess > 9)
			throw std::string("Division_guess must be greater than 1 and less than 10");

		bool positive_dividend = dividend > 0;
		bool positive_quotient = quotient > 0;

		bool add_next_digit = false;

		bool digit_inside_number = true;
		int starting_number = 0;
		int i = 0;
		while (starting_number < quotient && digit_inside_number)
		{
			starting_number += get_digit(dividend, i, &digit_inside_number);
			i++;
		}

		size_t number_positive_part_length = i;
		for (size_t j = i, bool inside_number; inside_number; j++, get_digit(dividend, j, &inside_number))
		{

		}

		if (starting_number > quotient)
		{
			do
			{

			} while (true);
		}

		double result = 0;

		
	}*/

	/// <summary>
	/// Grabs starting from left, the greater, the earlier. If i is negative the same rule will apply but for decimals
	/// </summary>
	static short get_digit(double number, int i, bool* digit_inside_number)
	{
		double original = number;
		number = abs(number);

		if (number < 10 && i == 0)
			return number;

		for (size_t j = 0; (j < abs(i)) && (i < 0); j++)
		{
			number *= 10;
		}

		if (digit_inside_number)
			*digit_inside_number = (number - (int)number) != 0 && i < 0;

		for (size_t j = 0; j < i; j++)
		{
			number /= 10;
		}

		if (digit_inside_number)
			*digit_inside_number = ((int)number != 0 && i >= 0) || digit_inside_number;

		//*digit_inside_number = (number != 0) || (!original && i == 0);
		number = (int)number;
		number /= 10.0;
		number -= (int)number;
		number *= 10;
		if (digit_inside_number)
			*digit_inside_number = number != 0 || *digit_inside_number;

		return number;
	}

	static void ReverseInplace(int* array, size_t array_length)
	{
		bool length_is_odd = array_length % 2;
		for (size_t i = 0; i < array_length / 2; i++)
		{
			size_t j = array_length - i - 1;
			int current_value = array[i];

			array[i] = array[j];
			array[j] = current_value;
		}
	}

	static int* TwoSum(DataStructures::SinglyLinkedListNode<int>* numbers, int target)
	{
		DataStructures::HashTable<int> table = DataStructures::HashTable<int>(100);

		DataStructures::SinglyLinkedListNode<int>* current_number = numbers;
		do
		{
			table.Add(current_number->value, current_number->value);

			current_number = current_number->next;
		} while (current_number);

		current_number = numbers;
		int result[2]{};
		bool is_found = false;
		size_t i = 0;
		do
		{
			int current = current_number->value;
			int searched = target - current;
			if (searched > 0)
			{
				table.Get(searched, is_found);
				result[0] = i;
				result[1] = searched;
			}

			current_number = current_number->next;
			i++;
		} while (current_number && !is_found);

		table.free();
		if (!is_found)
		{
			numbers->free();
			return 0;
		}

		is_found = false;
		current_number = numbers;
		i = 0;
		do
		{
			// Set result[1] to i if result[1] equals current number
			result[1] += (i - result[1]) * (current_number->value == result[1]);

			current_number = current_number->next;
			i++;
		} while (current_number && !is_found);

		numbers->free();
		return result;
	}
};

