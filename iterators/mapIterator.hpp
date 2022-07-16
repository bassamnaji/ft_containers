/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:14:34 by bnaji             #+#    #+#             */
/*   Updated: 2022/07/16 08:20:19 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include <iostream>
# include <string>
# include <memory>
# include <cstddef>
# include <cstdlib>
# include "../algorithms/pair.hpp"
# include "../algorithms/make_pair.hpp"
# include "../bst/avl.hpp"

namespace ft
{
  struct input_iterator_tag {};
  struct output_iterator_tag {};
  struct forward_iterator_tag : public input_iterator_tag {};
  struct bidirectional_iterator_tag : public forward_iterator_tag {};
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};

  template <class Iterator> struct iterator_traits
  {
   typedef typename Iterator::value_type        value_type;
   typedef typename Iterator::difference_type   difference_type;
   typedef typename Iterator::pointer           pointer;
   typedef typename Iterator::reference         reference;
   typedef typename Iterator::iterator_category iterator_category;
  };
  
  template <class T> struct iterator_traits<T*>
  {
    typedef T                                   value_type;
    typedef ptrdiff_t                           difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef random_access_iterator_tag          iterator_category;
  };
  
  template <class T> struct iterator_traits<const T*>
  {
    typedef T                                   value_type;
    typedef ptrdiff_t                           difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef random_access_iterator_tag          iterator_category;
  };

  template <class Category, class T, class Distance = std::ptrdiff_t,
	  	class Pointer = typename T::pointer, class Reference = typename T::reference>
	class iterator
	{
    public:
      
      typedef T                                value_type;
      typedef Distance                         difference_type;
      typedef Pointer                          pointer;
      typedef Reference                        reference;
      typedef Category                         iterator_category;

      iterator() : _node(NULL), _heighest(NULL), _lowest(NULL) { T dumb; _end = &dumb; }
      iterator(value_type * node) : _node(node) { _lowest = _node->getLowestKey(_node->getMasterRoot()); _heighest = _node->getHeighestKey(_node->getMasterRoot()); T dumb; _end = &dumb; }
      iterator (iterator const & src) : _node(NULL), _heighest(NULL), _lowest(NULL) { *this = src; T dumb; _end = &dumb; }
      ~iterator() {}

      iterator &		            operator = ( iterator<Category, const T> const & rhs ) { if (this != &rhs) { this->_node  = rhs._node; _lowest = rhs._lowest; _heighest = rhs._heighest; } return *this; }

      iterator &                operator ++ () { _increment(); return *this; }
      iterator                  operator ++ (int) { iterator tmp(*this); _increment(); return (tmp); }

      iterator &                operator -- () { _decrement(); return *this; }
      iterator                  operator -- (int) { iterator tmp(*this); _decrement(); return (tmp); }

      operator                  iterator<Category, const value_type>() { return iterator<Category, const value_type>(_node); }

      reference                 operator * () const { return this->_node->getPair(); }
      pointer                   operator -> () const { return this->_node->getPairPointer(); }

      template <class Iterator1, class Iterator2>
      friend bool operator== ( const Iterator1 & lhs,
                        const Iterator2 & rhs) { return lhs._node == rhs._node; }
      template <class Iterator1, class Iterator2>
      friend bool operator!= ( const Iterator1 & lhs,
                        const Iterator2 & rhs) { return lhs._node != rhs._node; }

    protected:
      value_type *                             _node;
      value_type *                             _heighest;
      value_type *                             _lowest;
      value_type *                             _end;

      void        _increment() {
        if (_node == _heighest)
          _node = _end;
        else if (_node == _end)
          _node = NULL;
        else if (_node->getRight()) {
          _node = _node->getRight();
          while (_node->getLeft())
            _node = _node->getLeft();
        }
        else if (_node->getParent()) {
          while (_node->getLess()(_node->getParent()->getPair().first, _node->getPair().first))
            _node = _node->getParent();
          _node = _node->getParent();
        }
      }

      void        _decrement() {
        if (_node == _lowest) {
          _node = NULL;
        }
        else if (_node->getLeft()) {
          _node = _node->getLeft();
          while (_node->getRight())
            _node = _node->getRight();
        }
        else if (_node->getParent()) {
          while (_node->getParent() && _node->getGreater()(_node->getParent()->getPair().first, _node->getPair().first)) {
            _node = _node->getParent();
          }
          if (_node->getParent())
            _node = _node->getParent();
        }
      }
	};



  template <class Iterator>
	class reverse_iterator : public iterator<typename Iterator::iterator_category, typename Iterator::value_type>
	{
    public:
      typedef typename iterator_traits<Iterator>::value_type            value_type;
      typedef typename iterator_traits<Iterator>::difference_type       difference_type;
      typedef typename iterator_traits<Iterator>::pointer               pointer;
      typedef typename iterator_traits<Iterator>::reference             reference;
      typedef typename iterator_traits<Iterator>::iterator_category     iterator_category;

      reverse_iterator() : iterator<iterator_category, value_type>(), _it(iterator<iterator_category, value_type>()) {}
      reverse_iterator(value_type * val) : iterator<iterator_category, value_type>(val) { _it = iterator<iterator_category, value_type>(val); }
      reverse_iterator(reverse_iterator const & src) : iterator<iterator_category, value_type>(src) { *this = src; }
      ~reverse_iterator() {}

      reverse_iterator &		            operator = ( reverse_iterator<Iterator> const & rhs ) { if (this != &rhs) { this->_node  = rhs._node; this->_lowest = rhs._lowest; this->_heighest = rhs._heighest; _it = rhs._it; } return *this; }

      reverse_iterator &                operator ++ () { --_it; return *this;}
      reverse_iterator                  operator ++ (int) { reverse_iterator tmp(*this); this->_decrement(); return (tmp); }

      reverse_iterator &                operator -- () { ++_it; return *this;}
      reverse_iterator                  operator -- (int) { reverse_iterator tmp(*this); this->_increment(); _it++; return (tmp); }

      operator reverse_iterator<iterator<iterator_category, const value_type> >() { return reverse_iterator<iterator<iterator_category, const value_type> >(this->_p); }

    private:
      Iterator _it;

	};
}

#endif /* ********************************************************** ITERATOR_H */