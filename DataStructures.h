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
			this->next = NULL;
		}

		SingleLinkedListNode* next;
		int value;
	};
};

