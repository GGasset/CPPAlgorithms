#include <iostream>
#include <string>

#pragma once
static class DataStructures
{
public:
	class SingleLinkedListNode
	{
	public:
		SingleLinkedListNode(int value)
		{
			this->value = value;
			this->next = 0;
		}

		SingleLinkedListNode* next;
		int value;

		SingleLinkedListNode* GetLastNode()
		{
			if (!this->next)
			{
				return this;
			}
			return this->next->GetLastNode();
		}

		SingleLinkedListNode* GetSecondToLastNode()
		{
			if (!this->next)
			{
				return this;
			}
			if (!this->next->next)
			{
				return this;
			}
			return GetSecondToLastNode();
		}

		SingleLinkedListNode* Reverse(SingleLinkedListNode* firstNode = NULL)
		{
			SingleLinkedListNode* output = new SingleLinkedListNode(this->value);

			if (!firstNode)
			{
				firstNode = output;
				return this->next->Reverse(firstNode);
			}



			if (!this->next)
			{
				return;
			}
			SingleLinkedListNode* new_first_node = this->next->Reverse(firstNode);
			new_first_node->next = new_first_node;
			return new_first_node;
		}

		std::string ToString()
		{
			if (!this->next)
				return std::to_string(this->value);
			return std::to_string(this->value) + "  ->  " + this->next->ToString();
		}

		void free()
		{
			if (this->next == 0)
			{
				std::free(this);
				return;
			}
			this->next->free();
		}
	};
};

