#pragma once
#include <iostream>

namespace JSTL
{
	template <typename T>
	struct FSingleNode
	{
		T            Data;
		FSingleNode* NextNode;
	};

	template <typename T>
	struct FDoubleNode
	{
		T            Data;
		FDoubleNode* NextNode;
		FDoubleNode* PrevNode;

		bool operator==(const FDoubleNode& OtherNode)
		{
			return this->Data == OtherNode.Data;
		}
	};


	template <typename T>
	class List
	{
		using Node = FDoubleNode<T>;

	public:
		List();

		void Insert(T Data);
		void Insert(T Data, int Index);

		void Remove(T Data);

		Node* Find(T Data, bool bStartFromTail);

		inline int Num() const { return mSize; }

		void PrintAll() const;

	private:
		int   mSize;
		Node* mHead;
		Node* mTail;
	};

#pragma region Implementation

	template <typename T>
	List<T>::List()
		: mSize(0),
		  mHead(nullptr),
		  mTail(nullptr)
	{
	}

	template <typename T>
	void List<T>::Insert(T Data)
	{
		Node* newNode = new Node;
		newNode->Data = Data;

		if (mSize == 0)
		{
			newNode->PrevNode = nullptr;
			newNode->NextNode = nullptr;

			mHead = newNode;
			mTail = mHead;
		}
		else
		{
			newNode->PrevNode = mTail;
			newNode->NextNode = nullptr;

			mTail->NextNode = newNode;
			mTail           = newNode;
		}

		mSize++;
	}

	template <typename T>
	void List<T>::Insert(T Data, int Index)
	{
		if (mSize > Index)
		{
			Node* nodeIterator = mHead;
			for (int i = 0; i < Index; ++i)
			{
				nodeIterator = nodeIterator->NextNode;
			}

			Node* newNode     = new Node;
			newNode->Data     = Data;
			newNode->PrevNode = nodeIterator;
			newNode->NextNode = nodeIterator->NextNode;

			if (nodeIterator->NextNode)
			{
				nodeIterator->NextNode->PrevNode = newNode;
			}

			nodeIterator->NextNode = newNode;

			mSize++;
		}
		else
		{
			Insert(Data);
		}
	}

	template <typename T>
	void List<T>::Remove(T Data)
	{
		Node* nodeIterator = mHead;

		while (nodeIterator)
		{
			if (nodeIterator->Data == Data)
			{
				if (nodeIterator->PrevNode)
				{
					nodeIterator->PrevNode->NextNode = nodeIterator->NextNode;
				}
				else
				{
					mHead = nodeIterator->NextNode;
				}

				delete nodeIterator;
				nodeIterator = nullptr;

				mSize--;

				return;
			}
			nodeIterator = nodeIterator->NextNode;
		}
	}

	template <typename T>
	typename List<T>::Node* List<T>::Find(T Data, bool bStartFromTail)
	{
		Node* nodeIterator = bStartFromTail ? mTail : mHead;

		while (nodeIterator)
		{
			if (nodeIterator->Data == Data)
				return nodeIterator;

			nodeIterator = bStartFromTail ? nodeIterator->PrevNode : nodeIterator->NextNode;
		}

		return nullptr;
	}

	template <typename T>
	void List<T>::PrintAll() const
	{
		Node* nodeIterator = mHead;

		while (nodeIterator)
		{
			std::cout << nodeIterator->Data << '\n'; // Data에 operator<< 구현되어 있어야 함
			nodeIterator = nodeIterator->NextNode;
		}
	}

#pragma endregion
}
