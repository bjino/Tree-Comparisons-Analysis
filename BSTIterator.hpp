#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include "BSTNode.hpp"
#include <list>
#include <iterator>

/**
 * Filename: BSTIterator.hpp
 * Assignment 1 CSE 100 
 * Date: 1/21/2015
 * Authors: Caitlin Cagampan and Nikkie Ella 
 * Description: This BSTIterator C++ file/class contains the constructor
 * 		operators for BSTNodes
 * Sources of Help: Piazza, Tutors, StackOverflow, Paul Kube Slides
 */

template<typename Data>
class BSTIterator : public std::iterator<std::input_iterator_tag,Data> {

private:

  BSTNode<Data>* curr;

public:

  /** Constructor.  Use the argument to initialize the current BSTNode
   *  in this BSTIterator.
   */ // 
  BSTIterator(BSTNode<Data>* curr) {
	this->curr = curr;

  }

  /** Dereference operator. */
  Data operator*() const {
    return curr->data;
  }
  
  /** Pre-increment operator. */
  BSTIterator<Data>& operator++() {
    curr = curr->successor();
    return *this;
  }

  /** Post-increment operator. */
  BSTIterator<Data> operator++(int) {
    BSTIterator before = BSTIterator(curr);
    ++(*this);
    return before;
  }

  /** Equality test operator. */ //
  bool operator==(BSTIterator<Data> const & other) const {
	return other.curr == curr;
  }

  /** Inequality test operator. */ // 
  bool operator!=(BSTIterator<Data> const & other) const {
	return other.curr != curr;
  }

};

#endif //BSTITERATOR_HPP
