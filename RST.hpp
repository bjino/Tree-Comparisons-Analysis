/******************************************************************************
 * NAME: BYRON JAY INOCENCIO
 *      CAITLIN CAGAMPAN
 *DATE: 1/28/2015
 *FILE: RST.hpp
 *OVERVIEW: Implements a randomized search tree dealing with BST properties,
 * random priorities, and tree rotations. 
 *ASSIGNMENT NUMBER: PA2
 *
 *
 * PA1 CODE USED: BST: Caitlin Cagampan (cs100wcw)
 *                RST INSERT: Solution file insert
 * CHANGES: We fixed the compiling error in BSTIterator.hpp by changing the 
 * equality operations from other->curr to other.curr. We also added a new
 * priority member in the BSTNode class. For the RST Insert, we ended up using
 * the solution files insert. The original insert that was written by Caitlin
 * creates a new node at the beginning, and then runs through a series of 
 * insertion logic. They also use a copy node to help compare data as the
 * logic in the code proceeded through the program. We chose to use the
 * solution code because it was more intuitively clear with the logic, and
 * creating the new node after finding the correct space in the tree AFTER
 * the logic works out better for our algorithm of RST insertion. We also
 * felt like it was more efficient since the solution file uses a last node
 * that just holds the last node to update the pointers AFTER insertion to
 * connect into the tree, which makes more intuitive sense as well. Another
 * reason we used the solution code was that our amount of comparisions rose
 * siginificantly with the use of Caitlins original code and occasional segfaults.
 * We were unable to pin down the exact causes, but we believe it has to do
 * with the order of logic within insertion that causes this, thus leading
 * us to go with the solution file code solely for RST insert (BST insert
 * still uses Caitlin's code)
 *
 *
******************************************************************************/

#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>
#include <time.h>

using namespace std;

template <typename Data>
class RST : public BST<Data> {

public:

  /* Insert new data into the RST if it is not already present.
   * 
   * Input
   *    item - the data to insert.
   *    return - true if the item was inserted. If the item was 
   *             already contained in the tree then return false
   */ 
  virtual bool insert(const Data& item) {
    
    //checks if the tree is empty. if it is, insert at root
    if (this->root == 0) {

      this->root = new BSTNode<Data>(item);

      setPriority(this->root); //gives the node a random priority
      return true; //returns true since we inserted the node
    
    } 

    //inserts for every other case besides root
    else {
    
      BSTNode<Data>* current = this->root; // sets a current pointer to root
      BSTNode<Data>* last = 0;             // declares a last pointer
      
      //runs while current is being occupied. ends when find an empty spot
      while ( current != 0 ) {
       
        //if items data is less than the current, go left
	if ( item < current->data ) {
	  last = current;
	  current = current->left;
	}

        //if items data is greater than current, go right
	else if ( current->data < item ) {
	  last = current;
	  current = current->right;
	
	} 
        
        else {  // already in the tree
	  return false;
	}
     }

      //create a new node to be inserted
      BSTNode<Data>* newNode = new BSTNode<Data>(item);

      //give the node a random priority
      setPriority(newNode);

      if ( item < last->data ) {
	last->left = newNode;
	newNode->parent = last;
      }

      //updates right pointer
      else {
	last->right = newNode;
	newNode->parent = last;
      }

      //bubbles the Node up to maintain heap order
       bubble(newNode);
      
      return true;
	
    }
  }

    

private:

  /* Perform a 'right rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes 
   * in the RST. This rotation is done by changing the 'left', 'right', and/or
   * 'parent' pointers of a subset of nodes without changing their
   * 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a left child
   *    child - the left child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order
   *   but switched in level, meaning 'par' will effectively 
   *   become the right-child of 'child'.
   *
   */
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {
    
    /* sets parents left to childs right */
    par->left = child->right;

    /* checks if the childs rights actually points to something. If it does
     * set it's parent pointer to par */
    if(child->right != 0)
        child->right->parent = par;

    /* make childs parent point to the grandparent */
    child->parent = par->parent;

    /* if we're rotating at root, update the root pointer */
    if(par->parent == 0)
         this->root = child;

    /* checks if par was a right child. if it is, set the grandparents
     * pointer back down to child accordingly */
    else if (par->parent->right == par)
         par->parent->right = child;

    /*else grandparent's left pointer points to child */
    else
       par->parent->left = child;
 
    child->right = par;       /*set childs right to the parent */
    par->parent = child;      /*set the parents parent point to child */
  }

  
  /* Perform a 'left rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes 
   * in the RST.This rotation is done by changing the 'left', 'right', and/or 
   * 'parent' pointers of a subset of nodes without changing their 'priority'
   * values.
   *
   * Input
   *    par - a parent node in the RST with a right child
   *    child - the right child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order 
   *   but switched in level, meaning 'par' will effectively become
   *   the left-child of 'child'.
   *
   */
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child ) {
    
    /* sets parents right pointer to childs left */ 
    par->right = child->left;

    /* checks if the childs left actually points to something. If it does,
     * set its parent pointer to par */
    if(child->left != 0)
       child->left->parent = par;
    
    /* make childs parent point to the grandparent */
    child->parent = par->parent;

    /* if we're rotating at root, update the root pointer */
    if(par->parent == 0)
       this->root = child;

    /* checks if par was a left child. If it is, set the grandparents
     * pointer back down to child accordingly */
    else if (par->parent->left == par)
       par->parent->left = child;

    /*else grandparent's left pointer points to child */
    else
       par->parent->right = child;

    child->left = par;       /*sets childs right to the parent */

    par->parent = child;    /*sets the parents parent point to child */
    

  }

  /* Gives the argument nodes priority a random value. This is implemented
   * using the rand() function
   *
   * Input
   *    theNode - the node that needs a randomized priority
   */
  void setPriority(BSTNode<Data>* theNode)
  { 
      theNode->priority = rand(); //gives the argument node a random priority

  }


  /* Bubbles the node up in the tree accordingly to maintain heap order
   * 
   * Input
   *    theNode - the node that needs to be put into the tree and
   *    bubbled up to maintain heap order
   */
  void bubble(BSTNode<Data>* theNode)
  {
  
      /*runs while theNode isn't the root & while heap order isn't fulfilled
        that is while the parents priority is greater than the current nodes */
       while(theNode->parent != 0 && theNode->parent->priority 
                   > theNode->priority){

              // checks if the child is a right child. if it is, rotate left
              if(theNode->parent->right == theNode)
                   rotateLeft(theNode->parent,theNode);

              // else rotate right
              else
                   rotateRight(theNode->parent,theNode);
 
              //updates the root pointer if the node is the new root
              if(theNode->parent ==0)
                 this->root = theNode;
       }
  }


public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Calls BST::insert so we can add data to test rotateRight and 
   * rotateLeft before implementing the fully correct version of RST::insert.
   * 
   */
  bool BSTinsert(const Data& item) {
    
    return BST<Data>::insert(item);
    
  }
  
  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Locates the node for an item and rotates it left or right without 
   * changing the left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with,
   *     1 if not. -1 if rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {
    
     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }
     
     if (current == 0 or current->data != item) {
       return 1;
     }
     
     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);
       
       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }
       
     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);
       
       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
