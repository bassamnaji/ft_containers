/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 07:48:29 by bnaji             #+#    #+#             */
/*   Updated: 2022/09/10 18:24:25 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <sstream>
# include <string>
# include <limits>
# include "../bst/avl.hpp"
# include "../iterators/mapIterator.hpp"
# include "../algorithms/utility.hpp"

namespace ft {
  template < class Key, class T, class Compare = std::less<Key>,
    class Alloc = std::allocator<ft::pair<const Key,T> > >
  class map {

  public:
    /* ************************************** Types ************************************** */
    typedef Key																													key_type;
    typedef T																														mapped_type;
    typedef Compare																											key_compare;
    typedef Alloc																												allocator_type;
    typedef ft::pair<const key_type,mapped_type>												value_type;
    typedef ft::AVL<const key_type, mapped_type, key_compare>			      avl_type;
    typedef typename allocator_type::template rebind<avl_type>::other   avl_allocator_type;
    typedef typename allocator_type::template rebind<key_type>::other   key_allocator_type;
    typedef typename allocator_type::reference													reference;
    typedef typename allocator_type::const_reference										const_reference;
    typedef typename allocator_type::pointer														pointer;
    typedef typename allocator_type::const_pointer											const_pointer;
    typedef typename ft::MapIterator<ft::bidirectional_iterator_tag,
                                            value_type, key_compare>    iterator;
    typedef typename ft::MapIterator<ft::bidirectional_iterator_tag,
                                      const value_type, key_compare>    const_iterator;
    typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;
    typedef ptrdiff_t																										difference_type;
    typedef size_t																											size_type;


    /* ************************************** Value_compare Class ************************************** */
    class value_compare
    {
      friend class map;
    protected:
      Compare comp;
      value_compare () {}
      value_compare (Compare c) : comp(c) {}
    public:
      typedef bool result_type;
      typedef value_type first_argument_type;
      typedef value_type second_argument_type;
      bool operator() (const value_type& x, const value_type& y) const {
        return comp(x.first, y.first);
      }
    };

    /* ************************************** Constructors ************************************** */
    inline explicit map (const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _root(NULL), _size(0), _comp(comp), _alloc(alloc),
      _avlAlloc(avl_allocator_type()), _keyAlloc(key_allocator_type()) { _createUselessEnd(); }

    template <class InputIterator>
    inline map (InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : _root(NULL), _size(0), _comp(comp), _alloc(alloc),
        _avlAlloc(avl_allocator_type()), _keyAlloc(key_allocator_type()) {
      _createUselessEnd();
      insert(first, last);
    }

    inline map (const map& x) : _root(NULL), _size(0), _comp(x._comp),
      _alloc(x._alloc), _avlAlloc(avl_allocator_type()), _keyAlloc(key_allocator_type()) {
      _createUselessEnd();
      *this = x;
    }
    
    inline ~map() { clear(); _deleteUselessEnd(); }
  
    inline map& operator= (const map& x);


    /* ************************************** Iterators ************************************** */
      inline iterator					        	  begin();

      inline const_iterator 		        	begin() const;

      inline iterator					        	  end();

      inline const_iterator 		        	end() const;

      inline reverse_iterator						  rbegin();

      inline const_reverse_iterator 			rbegin() const;

      inline reverse_iterator						  rend();

      inline const_reverse_iterator 			rend() const;


      /* ************************************** Capacity ************************************** */
      inline bool                        empty() const;

      inline size_type                   size() const;

      inline size_type                   max_size() const;


      /* ************************************** Element Access ************************************** */
      mapped_type& operator[] (const key_type& k);
      
      mapped_type& at (const key_type& k);

      const mapped_type& at (const key_type& k) const;


      /* ************************************** Modifiers ************************************** */
      ft::pair<iterator,bool> insert (const value_type& val);

      iterator insert (iterator position, const value_type& val);

      template <class InputIterator>
      void insert (InputIterator first, InputIterator last);
      
      void erase (iterator position);

      size_type erase (const key_type& k);

      void erase (iterator first, iterator last);

      void swap (map& x);

      void clear();

      
      /* ************************************** Observers ************************************** */
      key_compare key_comp() const;

      value_compare value_comp() const;

      
      /* ************************************** Operations ************************************** */
      iterator find (const key_type& k);

      const_iterator find (const key_type& k) const;

      size_type count (const key_type& k) const;

      iterator lower_bound (const key_type& k);

      const_iterator lower_bound (const key_type& k) const;

      iterator upper_bound (const key_type& k);

      const_iterator upper_bound (const key_type& k) const;

      ft::pair<iterator,iterator>             equal_range (const key_type& k);

      ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;


      /* ************************************** Allocator ************************************** */
      allocator_type get_allocator() const;

      private:
        avl_type *                      _root;
        size_type                       _size;
        key_compare                     _comp;
        allocator_type                  _alloc;
        avl_allocator_type              _avlAlloc;
        key_allocator_type              _keyAlloc;
        avl_type *                      _uselessEnd;
        void                            _createUselessEnd();
        void                            _deleteUselessEnd();
  };
}

#include "map.tpp"

#endif
