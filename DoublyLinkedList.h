#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>
#include <iostream>


using namespace std;

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;//next 대신.
		Node* right = nullptr;//next 대신.
	};

	DoublyLinkedList()
	{
	}
    //이니셜라이즈 리스트

	~DoublyLinkedList()
	{
		Clear();
	}//소멸자

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node* current = first_;

        while(current->left != nullptr){
            current = current ->left;
        }

        while(current != nullptr){
            Node* temp = current;
            current = current->right;
            delete temp;
        }
	}

	bool IsEmpty()
	{
        if(first_) return false;
        return true;
	}

	int Size()
	{
		int size = 0;

        Node* cur = first_;

		while(cur){
            cur = cur->left;//left로 쭉 밀어놓고 
        }
        while(cur){
            cur = cur-> right;//오른쪽으로 가면서 전체 개수 세기
            size++;
        }

		return size;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
        else
		{
			cout << "Size = " << Size() << endl;
			cout << " Forward: "; 
            //        ->
			while(current){
                cout << current-> item;
                current = current-> right;
            }
			cout << endl;

			cout << "Backward: "; //     <-
			Node* current1 = first_;

            while(current1){
                cout << current1-> item;
                current1 = current1-> left;
            }
			cout << endl;
		}
	}

	Node* Find(T item)
	{
        Node* current = first_;

        while( current && current->item != item){
            current = current->right;
        }
        
         while(current && current->item != item){
            current = current-> left;
        }
        return current;

	}

	void InsertBack(Node* node, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			Node* current = first_-> right;
            Node* prev = first_;
            
            while(prev != node){

            prev = current;
            current = current-> right;
                
            }//node = prev, node-> right =current

            prev-> right = new Node;//prev = node;
            Node * temp = prev -> right;// 노드 다음 새로운 공간 창출;

            temp -> item = item;//그공간에 값 집어넣기.
            temp -> right = current; //
		}
	}

	void PushFront(T item)
	{//아무것도 없을때 변수 if 제대로 못만듦 수정 요구함.
        Node* current = first_;

        if(IsEmpty()){
        first_ = new Node;

        first_ -> item = item;
        first_ -> left = nullptr;
        
        return; 
        }
		

        while(current->left != nullptr){
            current = current-> left;
        }//맨왼쪽 노드 을 찾은거 아냐.

        current->left = new Node;
        Node* temp = current ->left;

        temp -> item = item;
        temp -> left = nullptr;
	}

	void PushBack(T item)
	{
		Node* current = first_;

        while(current->right != nullptr){

            current = current-> right;
        }//맨 오른쪽 노드 을 찾은거 아냐.

        current->right= new Node;
        Node * temp = current->right;

        temp-> item = item;
        temp-> right = nullptr;
    
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

        Node* current = first_->left;
        Node* prev =first_;

        while(current->left != nullptr){
            current = current->left;
            prev = current;
        }//깨고 나오면 current는 맨 왼쪽 노드, prev는 그 전 노드가 되는 거겠지.

        delete current;
        prev->left = nullptr;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		Node* current = first_ -> right;
        Node* prev = first_;

        while(current -> right != nullptr){
            current = current -> right;
            prev = current;
        }//깨고 나오면 current는 맨 왼쪽 노드, prev는 그 전 노드가 되는 거겠지.

        delete current;
        prev-> right = nullptr;
		
	}

	void Reverse()
	{//애매함.설명을  더해주지.
		Node* current = first_;
        Node* prev = first_ -> left;

        while(current != nullptr){
          
            current ->left = prev;
            prev = current;
            current = current -> right;
        }//current 는 널인데..?
        prev = first_;
        prev -> right = nullptr;

	}

	T Front()
	{
		assert(first_);
        Node* current = first_;

        while(current-> right != nullptr){
            current = current-> right;
        }
        return current->item;

	}

	T Back()
	{
		assert(first_);

		Node* current = first_;

        while(current-> left != nullptr){
            current = current-> left;
        }
        return current->item;
	}

protected:
	Node* first_ = nullptr;
};