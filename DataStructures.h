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
			if (this->next == 0)
			{
				return this;
			}
			return this->next->GetLastNode();
		}

		SingleLinkedListNode* GetSecondToLastNode()
		{
			if (this->next == 0)
			{
				return this;
			}
			if (this->next->next == 0)
			{
				return this;
			}
			return GetSecondToLastNode();
		}
	};
};

