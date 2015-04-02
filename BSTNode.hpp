#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/**
 * Filename: BSTNode.hpp
 * Assignment 1 CSE 100
 * Date: 1/21/2015
 * Author: Caitlin Cagampan and Nikkie Ella
 * Description:Class definition for BSTNode, which is the element that gets 
 * inserted into  a Binary Search Tree. Includes the datafields left, right, 
 * and parent (which are of type BSTNode<Data>*), and data (which is of
 * type Data const) to BSTNodes. 
 * Sources of Help: Piazza, Tutors, StackOverflow, Paul Kube Slides
 *
 */

template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  int priority;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */
  BSTNode<Data>* successor() {
 
	//Node to return
	BSTNode<Data>* current = this;

	//Case if there is a right child
	if (this->right) {

		//Move right once
		current = this->right;
		
		//Move all the way left
		while (current != 0) {

			if (current->left)
				current = current->left;
			else
				break;		
		}
		
		return current;
	}	

	//Case if there is no right child
	else {

		//Move upwards until you find a node that's bigger 
		while (current != 0) {
		
			if (current->parent) {

				if (current->data < current->parent->data) {
					
					current = current->parent;	
					break;

				} else
					current = current->parent;

			} else

				//Case if there's no right child or parent
				return 0;
		}
		
		return current;
	} 
}

   }; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
