/**
 * @file lab8.cpp
 * @author Khalid Mengal
 * @description BST Tree implementation in C++
 * @date 2022-11-03
 */
#pragma once
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>

using namespace std;
template <typename T1, typename T2>
class Node
{
	private:
		T1 key;					//city name
		vector<T2> value;		//list of hotels in the city
		Node<T1,T2>* left;		//left child
		Node<T1,T2>* right;		//right child
		Node<T1,T2>* parent;	//pointer to the parent node
	public:
		Node(T1 key): key(key),left(nullptr),right(nullptr), parent(nullptr) 
		{}
		void print(string stars="")	//print all or only those hotels with specific stars.
		{
			int counter=0;
			cout<<std::left<<setw(50)<<"Name"<<" "<<setw(10)<<"City"<<" "<<setw(5)<<"Stars"<<" "<<setw(10)<<"Price"<<" "<<setw(20)<<"Country"<<" "<<"Address"<<endl;
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;

			for(auto it:value)
				if(stars=="" or stars==it->getStars())
				{
					it->print2();
					counter++;
				}
			
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<counter<<" records found."<<endl;
		}

		template<typename,typename> friend class BST;
};
//=============================================================================
template <typename T1, typename T2>
class BST
{
	private:
		Node<T1,T2> *root;
	public:
		BST();									//constructor
		~BST();									//destructor
		Node<T1,T2>*& getRoot();						//returns the root of the Tree
		void insert(Node<T1,T2>*& ptr,T1 key, T2 value);			//Insert key into tree/subtree with root ptr
		int height(Node<T1,T2> *ptr);				    //Find the height of a tree/subtree with root ptr
		Node<T1,T2>* find(Node<T1,T2> *ptr,T1 key,string stars);		//Find and returns the node with key
		Node<T1,T2>* findMin(Node<T1,T2> *ptr, T1 key);				//Find and return the Node<T1,T2> with minimum key value of the tree/subtree with root ptr
		void remove(Node<T1,T2>* ptr,T1 key, T2 value);			//Remove a node with key from the tree/subtree with root

		void destructor_helper(Node<T1,T2> *ptr); // Helper method for the destructor
};
//=====================================================================
//write implementation of all methods below
template <typename T1, typename T2>
BST<T1, T2>::BST() {
	this->root = nullptr; // initialise the root
}

template <typename T1, typename T2>
Node<T1,T2>*& BST<T1, T2>::getRoot(){
	return root; // Return the root
}

// Insert a node in the BST
template <typename T1, typename T2>
void BST<T1, T2>::insert(Node<T1, T2>*& ptr, T1 key, T2 value) {
	// Check if the current pointer (ptr) is null, indicating that we are at a position where the new node should be inserted.
    if (ptr == nullptr) {
        ptr = new Node<T1, T2>(key); // Create a new node with the given key.
        ptr->value.push_back(value); // Add the value to the vector of values in the new node.
    } else if (ptr->key == key) { // If the current node's key matches the key to be inserted.
    	// Iterate through the vector of values in the current node
    	for(int i = 0; i < ptr->value.size(); i++){ 
    		if(ptr->value[i]->getName() == value->getName()){
    			ptr->value[i] = value; // If it matches, update the value.
    			return; // Exit the function as the value has been updated.
    		}
    	}

        ptr->value.push_back(value); // If no matching name is found, add the new value to the vector of values in the current node.
    } else if (ptr->key < key) {
        insert(ptr->right, key, value); // Recursively call insert on the right subtree.
    } else if (ptr->key > key) {
        insert(ptr->left, key, value); // Recursively call insert on the left subtree.
    }
}

//Find the height of a tree/subtree with root ptr
template <typename T1, typename T2>
int BST<T1, T2>::height(Node<T1,T2> *ptr){
	if(ptr == nullptr){
		return -1; // the height of an empty tree is -1
	}

	return 1 + max(height(ptr->left), height(ptr->right)); // Calls the function recursively
}


//Find and returns the node with key
template <typename T1, typename T2>
Node<T1, T2>* BST<T1, T2>::find(Node<T1, T2>* ptr, T1 key, string stars) {
	if (ptr == nullptr || ptr->key == key) {
        return ptr; // Return the node if found or null
    }

    if (ptr->key < key) {
        return find(ptr->right, key, stars); // Search in the right subtree of the tree rooted at ptr
    } else {
        return find(ptr->left, key, stars); // Search in the left subtree of the tree rooted at ptr
    }
}

//Find and return the Node<T1,T2> with minimum key value from the right side of the tree/subtree with root ptr
template <typename T1, typename T2>
Node<T1, T2>* BST<T1, T2>::findMin(Node<T1, T2>* ptr, T1 key) {
	Node<T1, T2>* tracker = ptr; // Assign a ptr to a node "tracker"

    // Re-iterate as long as the tracker is not null and it has a left child
    while(tracker != nullptr && tracker->left != nullptr){
        tracker = tracker->left; // Keep going to the left
    }

    return tracker; // Returns the left-most node (which is the minimum of the BST)
}

//Remove a node with key from the tree/subtree with root
template <typename T1, typename T2>
void BST<T1, T2>::remove(Node<T1, T2>* ptr, T1 key, T2 value) {
    // Find the node
    Node<T1, T2>* node = find(ptr, key, ""); // Search for the node to be deleted

    if (node == nullptr) {
        return;  // Node not found
    }

    // We look for the element in the vector that is equal to "value" and we erase it from the vector
	for(int i = 0; i < node->value.size(); i++){
		if(node->value[i] == value){
			node->value.erase(node->value.begin()+(i));
		}
	}

	// If the vector is empty we delete the node all together
    if(node->value.empty() || value == nullptr){
	    // Node with two children
	    if (node->left != nullptr && node->right != nullptr) {
	        Node<T1, T2>* successor = findMin(node->right, key);
	        node->key = successor->key;
	        node->value = successor->value;
	        remove(node->right, successor->key, value); // Remove the successor
	    }
	    // Node with only one child or no child
	    else {
	        Node<T1, T2>* temp = nullptr;
			if(node->left != nullptr){
			    temp = node->left;
			}else{
			    temp = node->right;
			}

	        // No child case
	        if(temp == nullptr){
	            temp = node;
	            node = nullptr;
	        }else{  // One child case
	        	// Copy the contents
	            node->key = temp->key;  
	            node->value = temp->value;
	        }

	        delete temp;  // Free the memory
	    }

	    // Update parent links if necessary
	    if(node != nullptr && node->parent != nullptr){
	        if(node->parent->left == node){
	            if(node->left != nullptr){
				    node->parent->left = node->left;
				}else{
				    node->parent->left = node->right;
				}

	        }else{
	            if(node->right != nullptr){
				    node->parent->right = node->right;
				}else{
				    node->parent->right = node->left;
				}
	        }

	        if(node->left != nullptr){
	            node->left->parent = node->parent;
	        }
	        if(node->right != nullptr){
	            node->right->parent = node->parent;
	        }
	    }

	    // If the node to delete is the root
	    if (ptr == node) {
	        if (node->left != nullptr) {
			    ptr = node->left;
			} else {
			    ptr = node->right;
			}

	    }
	}
}

// Helper function that deletes a node and its descendents
template <typename T1, typename T2>
void BST<T1,T2>::destructor_helper(Node<T1,T2> *ptr){
	if(ptr == nullptr){
		return;
	}
	if(ptr->left != nullptr){
		destructor_helper(ptr->left);
	}
	if(ptr->right != nullptr){
		destructor_helper(ptr->right);
	}

	delete ptr;

}

// Destructor
template <typename T1, typename T2>
BST<T1, T2>::~BST() {
	destructor_helper(root);
}
