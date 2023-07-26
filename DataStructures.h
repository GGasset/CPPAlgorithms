#include <iostream>
#include <string>

#pragma once
static class DataStructures
{
public:
	template <typename T>
	class SinglyLinkedListNode
	{
	public:
		SinglyLinkedListNode(T value)
		{
			this->value = value;
			this->next = 0;
		}

		SinglyLinkedListNode* next;
		int value;

		SinglyLinkedListNode& operator[](int i)
		{
			return GetIndex(i);
		}

		SinglyLinkedListNode* GetIndex(size_t i)
		{
			if (i == 0)
			{
				return this;
			}
			
			if (!this->next)
			{
				return NULL;
			}

			return GetIndex(i - 1);
		}

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

	template <typename valueT>
	class HashTable
	{
	private:
		SinglyLinkedListNode<int>** keys;
		SinglyLinkedListNode<valueT>** values;

	public:
		__readonly int bucket_count;

		HashTable(int bucket_count)
		{
			this->bucket_count = bucket_count;
			this->keys = (SinglyLinkedListNode<int>**)malloc(sizeof(SinglyLinkedListNode<int>*) * bucket_count);
			this->values = (SinglyLinkedListNode<valueT>**)malloc(sizeof(SinglyLinkedListNode<valueT>*) * bucket_count);
		}

		int GetHash(int key)
		{
			int hash = key;
			hash = hash * (hash < bucket_count) + (bucket_count % hash) * (hash >= bucket_count);

			return hash;
		}

		void Add(int key, valueT value)
		{
			int bucketI = GetHash(key);
			InsertAtBucket(key, value, bucketI);
		}

		valueT Get(int key)
		{

		}

	private:
		void InsertAtBucket(int key, valueT value, int bucket_i)
		{
			if (!this->keys[bucket_i])
			{
				this->keys[bucket_i] = new SinglyLinkedListNode<int>(key);
				this->values[bucket_i] = new SinglyLinkedListNode<valueT>(value);
				return;
			}

			this->keys[bucket_i]->GetLastNode()->next = new SinglyLinkedListNode<int>(key);
			this->values[bucket_i]->GetLastNode()->next = new SinglyLinkedListNode<valueT>(value);
		}

		valueT GetValueAtBucket(valueT value, int bucket_i, int node_i)
		{
			
		}
	};
};

