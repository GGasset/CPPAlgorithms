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
	};
};

