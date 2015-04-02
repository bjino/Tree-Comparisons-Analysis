#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

/**
 * Filename: BST.hpp
 * Assignment 1 CSE 100 
 * Date: 1/21/2015
 * Authors: Caitlin Cagampan and Nikkie Ella
 * Description: This BST C++ file/class contains functions that specifically 
 * 		cater to a Binary Search Tree including inserting into a Binary
 * 		Search Tree and also checking the size. It also implements 
 * 		a BSTIterator to find a specific node whether specified, in the
 * 		beginning, or at the end. This file is important as it uses 
 * 		the BSTNode and BSTIterator file in order to apply functions. 
 * 
 * Sources of Help: Piazza, Tutors, StackOverflow, Paul Kube Slides
 *
 * AMENDMENTS FOR PA2: This BST.hpp file contains solution code for the
 *                     the find method. We use the provided solution code
 *                     for the find method due to the fact that the
 *                     previously implementation had too many comparisons
 *                     and was not efficient, thus giving us a higher
 *                     amount of comparisions that expected.
 */

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // 
  virtual ~BST() {
	
	deleteAll(root);
	
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ //

 /**
  * Function name: virutal bool insert 
  * Function prototype: virtual bool insert(const Data& item)
  * Description: Inserts a node with data into the BST
  * Parameters: constData& item
  * Return Value: boolean
  */  
  virtual bool insert(const Data& item) {

	//Create a node storing the data from item
	BSTNode<Data>* copy = new BSTNode<Data> (item);	

	//Node to compare "copy" variable to
	BSTNode<Data>* current; 
		
	//Check if first insertion
	if (root == 0) {
		
		root = copy;
		isize++;		

	} else {

		current = root;	
		
		//Traverse through the tree to find an appropriate 
		//place of insertion
		while (current != 0) {

			//Get rid of repeated node
			if (copy->data == current->data) {
				
				delete copy;	
				return false;	

			}

			//Check left
			else if (copy->data < current->data) {
				
				//Found empty spot to insert
				if (current->left == 0) {

	 				current->left = copy;

					//Set parent of inserted node
					copy->parent = current;

					isize++;
					break;

				} else
					//Continue traversing
					current = current->left;
			} 		
	
			//Check right
			else {

				//Found empty spot to insert
				if (current->right == 0) {

					current->right = copy;

					//Set parent of inserted node
					copy->parent = current;

					isize++;
					break;

				} else
					//Continue traversing
					current = current->right;	
			}
		}
	}

	return true;
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ //

  /**
   *  Function name: iterator find 
   *  Function prototype: iterator find(const Data& item) const
   *  Description: This function finds data from a specific node and returns it
   *  Parameters: const Data& item
   *  Return Value: the iterator data 
   **/  
  iterator find(const Data& item) const {

     BSTNode<Data>* current = root;
     while(current !=0) {
       if (item <current->data){
           current = current->left;
      }
       else if(current->data < item){
           current = current->right;
      }
       else{
          return iterator(current);
       }
    }
      return end();
  }

  
  /** Return the number of items currently in the BST.
   */ // 
  unsigned int size() const {
	return isize;
  }

  /** Return true if the BST is empty, else false.
   *  
   *  Parameter: None
   *  Return value: Boolean- true or false
   */ // 
  bool empty() const {

	if (isize == 0) 
		return true;
	else 
		return false;
  }

  /** Return an iterator pointing to the first item in the BST 
   * (not the root).
   *  Parameter: None
   *  Return value: iterator data of the first item 
   */ //
  iterator begin() const {
	
	//Initialize iterator to return
  /*	BSTIterator<Data>* workingNode = new BSTIterator<Data>(first(root));
	return *workingNode;
   */
	return typename BST<Data>::iterator(first(root));

}

  /** Return an iterator pointing past the last item in the BST.
   *  Parameter: None
   *  Return value: iterator data of the last item
   *
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending
   * order. Implementing inorder and deleteAll base on the pseudo code is 
   * an easy way to get started.
   */ //

  /**
   * Function name: void inorder
   * Function prototype: void inorder(BSTNode<Data>* n) const
   * Description: Helper function that prints out a BST in order using an 
   * 		  inorder traversal. 
   * Parameters: BSTNode<Data>* n
   * Return Value: none
   **/  
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
	
	//Check if current node exists
	if(n == 0) return;

	//Recursively traverse left
	if(std::left){
	     inorder(n->left);
	}
	
	//Print current node data
	std::cout << n->data << std::endl;	

	//Recursively traverse right
	if(std::right) {
      	     inorder(n->right);
	}
	
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   */ //-
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */
	//Check if current node exists
	if(n == 0) return;

	//Recursively delete the left
	if(std::left){
		deleteAll(n->left);
	}

	//Recursively delete the right
	if(std::right){
		deleteAll(n->right);
	}

	delete n;
	
}


 };


#endif //BST_HPP
