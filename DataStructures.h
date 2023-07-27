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
		T value;

		SinglyLinkedListNode& operator[](int i)
		{
			return *GetIndex(i);
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

		int GetValueIndex(T value, int i = 0)
		{
			if (this->value == value)
				return i;
			if (!this->next)
				return -1;
			return this->next->GetValueIndex(value, i++);
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
			if (!std::is_same<T, std::string>() && !std::is_same<T, int>())
			{
				if (!this->next)
					return std::to_string(this->value);
				return std::to_string(this->value) + "  ->  " + this->next->ToString();
			}
			else
				throw "Type not supported at linkedList ToString()";
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
		bool* contains_values;

	public:
		__readonly int bucket_count;

		HashTable(int bucket_count)
		{
			this->bucket_count = bucket_count;
			this->keys = (SinglyLinkedListNode<int>**)malloc(sizeof(SinglyLinkedListNode<int>*) * bucket_count);
			this->values = (SinglyLinkedListNode<valueT>**)malloc(sizeof(SinglyLinkedListNode<valueT>*) * bucket_count);
			this->contains_values = (bool*)malloc(sizeof(bool) * bucket_count);
			for (size_t i = 0; i < bucket_count; i++)
			{
				this->contains_values[i] = false;
			}
		}

		int GetHash(int key)
		{
			int hash = key;
			hash = hash * (hash < bucket_count) + (bucket_count % hash) * (hash >= bucket_count);
			hash -= bucket_count * (hash == bucket_count);

			return hash;
		}

		void Add(int key, valueT value)
		{
			int bucketI = GetHash(key);
			InsertAtBucket(key, value, bucketI);
		}

		valueT Get(int key, bool &is_found)
		{
			int bucket_i = GetHash(key);
			is_found = contains_values[bucket_i];
			if (!is_found)
				throw std::string("Value not found");

			int node_i = keys[bucket_i]->GetValueIndex(key);

			is_found = node_i != -1;
			if (!is_found)
				return 0;

			return GetValueAtBucket(bucket_i, node_i);
		}

	private:
		void InsertAtBucket(int key, valueT value, int bucket_i)
		{
			if (!this->contains_values[bucket_i])
			{
				this->keys[bucket_i] = new SinglyLinkedListNode<int>(key);
				this->values[bucket_i] = new SinglyLinkedListNode<valueT>(value);
				this->contains_values[bucket_i] = true;
				return;
			}

			this->keys[bucket_i]->GetLastNode()->next = new SinglyLinkedListNode<int>(key);
			this->values[bucket_i]->GetLastNode()->next = new SinglyLinkedListNode<valueT>(value);
		}

		valueT GetValueAtBucket(int bucket_i, int node_i)
		{
			//SinglyLinkedListNode<valueT> *bucket = ;
			return values[bucket_i]->GetIndex(node_i)->value;
		}
	};
};

