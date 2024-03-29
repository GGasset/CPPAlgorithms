#include <iostream>
#include <string>
#include <functional>

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

		SinglyLinkedListNode* operator[](int i)
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

			return next->GetIndex(i - 1);
		}

		size_t GetLastIndex(T value)
		{
			int output = -1;

			SinglyLinkedListNode<T>* current = this;
			size_t i = 0;
			while (current)
			{
				output += (i - output) * (value == current->value);

				i++;
				current = current->next;
			}

			return output;
		}

		int GetValueIndex(T value, int i = 0)
		{
			if (this->value == value)
				return i;
			if (!this->next)
				return -1;
			return this->next->GetValueIndex(value, i++);
		}

		size_t Count(T value, size_t starting_count = 0)
		{
			starting_count += value == this->value;
			if (this->next)
			{
				starting_count += this->next->Count(value, starting_count);
			}
			return starting_count;
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

		static SinglyLinkedListNode<T>* AddRange(SinglyLinkedListNode<T>* start_node,
			T* values, size_t array_length, size_t values_start_i = 0,
			SinglyLinkedListNode<T>* node_after_last_created_node = 0, SinglyLinkedListNode<T>* current_node = 0)
		{
			start_node = start_node ? start_node : new SinglyLinkedListNode<T>(0);

			current_node = current_node ? current_node : start_node;
			current_node->value = values[values_start_i];

			if (values_start_i < array_length)
			{
				start_node->next = AddRange(start_node, values, array_length, values_start_i + 1, node_after_last_created_node, current_node->next);
				return start_node;
			}

			current_node->next = node_after_last_created_node;
			return start_node;
		}

		T* ToArray(bool free_nodes = false, size_t i = 0, T* array = 0)
		{
			if (!array)
			{
				size_t list_length = GetLength();
				array = new T[list_length];
			}

			array[i] = this->value;
			if (this->next)
			{
				this->next->ToArray(false, i + 1, array);
			}
			if (free_nodes)
			{
				this->free();
			}
			return array;
		}

		std::string ToString()
		{
			if (!this->next)
				return std::to_string(this->value);
			return std::to_string(this->value) + "==>" + this->next->ToString();
		}

		void free()
		{
			if (!this->next)
			{
				std::free(this);
				return;
			}
			this->next->free();
		}

		bool iterate(std::function<bool(SinglyLinkedListNode* current, int i)> iterateFunc, int i = 0)
		{
			bool current_out = iterateFunc(this, i);
			if (this->next)
			{
				return current_out || this->next->iterate(iterateFunc, i + 1);
			}
		}

		size_t GetLength(size_t i = 1)
		{
			if (!this->next)
			{
				return i;
			}
			return this->next->GetLength(i + 1);
		}
	};

	template <typename keyT, typename valueT>
	class HashTable
	{
	private:
		SinglyLinkedListNode<keyT>** keys;
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
			for (size_t i = 0; i < bucket_count && contains_values; i++)
			{
				this->contains_values[i] = false;
			}
		}

		virtual size_t GetHash(keyT key)
		{
			if (typeid(keyT) == typeid(short) || typeid(keyT) == typeid(int) || typeid(keyT) == typeid(size_t) || typeid(keyT) == typeid(long) || typeid(keyT) == typeid(long long))
			{
				int hash = key;
				hash = hash * (hash < bucket_count) + (bucket_count % hash) * (hash >= bucket_count);
				hash -= bucket_count * (hash == bucket_count);

				return hash;
			}
			if (typeid(keyT) == typeid(char*) || typeid(keyT) == typeid(std::string))
			{
				size_t hash = 0;

				char currentC;
				size_t i = 0;
				/*std::string parsed_key = std::string(key);
				while (currentC = parsed_key[i] && i < 20)
				{
					hash += currentC;
				}*/
				
				hash %= bucket_count;

				return hash;
			}
		}

		void Add(keyT key, valueT value)
		{
			size_t bucketI = GetHash(key);
			InsertAtBucket(key, value, bucketI);
		}

		valueT Get(keyT key, bool& is_found)
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

		void free()
		{
			for (size_t i = 0; i < bucket_count && keys && values; i++)
			{
				keys[i]->free();
				values[i]->free();
			}
			std::free(keys);
			std::free(values);
			std::free(contains_values);
		}

	private:
		void InsertAtBucket(keyT key, valueT value, int bucket_i)
		{
			if (!this->contains_values[bucket_i])
			{
				this->keys[bucket_i] = new SinglyLinkedListNode<keyT>(key);
				this->values[bucket_i] = new SinglyLinkedListNode<valueT>(value);
				this->contains_values[bucket_i] = true;
				return;
			}

			this->keys[bucket_i]->GetLastNode()->next = new SinglyLinkedListNode<keyT>(key);
			this->values[bucket_i]->GetLastNode()->next = new SinglyLinkedListNode<valueT>(value);
		}

		valueT GetValueAtBucket(int bucket_i, int node_i)
		{
			//SinglyLinkedListNode<valueT> *bucket = ;
			return values[bucket_i]->GetIndex(node_i)->value;
		}
	};
};
