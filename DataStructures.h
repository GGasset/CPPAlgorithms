#include <iostream>
#include <string>

#pragma once
static class DataStructures
{
public:
	class SinglyLinkedListNode
	{
	public:
		SinglyLinkedListNode(int value)
		{
			this->value = value;
			this->next = 0;
		}

		SinglyLinkedListNode* next;
		int value;

		SinglyLinkedListNode* GetLastNode()
		{
			if (!this->next)
			{
				return this;
			}
			return this->next->GetLastNode();
		}

		SinglyLinkedListNode* GetSecondToLastNode()
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

		SinglyLinkedListNode* Reverse(SinglyLinkedListNode* firstNode = NULL)
		{
			SinglyLinkedListNode* new_first_node = new SinglyLinkedListNode(this->value);

			new_first_node->next = firstNode;

			if (!this->next)
			{
				return new_first_node;
			}

			if (!firstNode)
			{
				firstNode = new_first_node;
				return this->next->Reverse(firstNode);
			}

			return this->next->Reverse(new_first_node);
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

	class HashTable
	{
	private:
		SinglyLinkedListNode* nodes;

	public:
		__readonly int bucket_count;

		HashTable(int bucket_count)
		{
			this->bucket_count = bucket_count;
			this->nodes = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode) * bucket_count);
		}
	};
};

