/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 08:12:55 by bnaji             #+#    #+#             */
/*   Updated: 2022/06/25 08:19:00 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft
{  
  template <class InputIterator1, class InputIterator2>
  bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
  {
    while (first1 != last1) {
      if (!(*first1 == *first2))
        return false;
      ++first1; ++first2;
    }
    return true;
  }

  template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
  {
    while (first1 != last1) {
      if (!pred(*first1,*first2))
        return false;
      ++first1; ++first2;
    }
    return true;
  }
}

#endif