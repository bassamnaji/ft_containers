/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vTPrinter.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnaji <bnaji@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:02:10 by bnaji             #+#    #+#             */
/*   Updated: 2022/07/02 07:35:30 by bnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "vectorTests.hpp"

template<typename T>
void printStdVec(std::vector<T> const & v) {
  std::cout << PURPLE << "v             : " << YELLOW;
  for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); it++)
    std::cout << *it << ' ';
  std::cout << RESET << std::endl;
}

template<typename T>
void  printStdVecSize(std::vector<T> const & v) {
  std::cout << PURPLE << "v size        : " << YELLOW << v.size() << RESET << std::endl;
}

template<typename T>
void  printStdVecCap(std::vector<T> const & v) {
  std::cout << PURPLE << "v capacity    : " << YELLOW << v.capacity() << RESET << std::endl;
}

template<typename T>
void printMyVec(ft::vector<T> const & ft_v) {
  std::cout << PURPLE << "ft_v          : " << YELLOW;
  for (typename ft::vector<T>::const_iterator it = ft_v.begin(); it != ft_v.end(); it++)
    std::cout << *it << ' ';
  std::cout << RESET << std::endl;
}

template<typename T>
void  printMyVecSize(ft::vector<T> const & ft_v) {
  std::cout << PURPLE << "ft_v size     : " << YELLOW << ft_v.size() << RESET << std::endl;
}

template<typename T>
void  printMyVecCap(ft::vector<T> const & ft_v) {
  std::cout << PURPLE << "ft_v capacity : " << YELLOW << ft_v.capacity() << RESET << std::endl;
}

template<typename T>
void printVecIters(T ft_it, T it) {
  std::cout << PURPLE << "it    : " << YELLOW << it << RESET << std::endl;
  std::cout << PURPLE << "ft_it : " << YELLOW << ft_it << RESET << std::endl;
}

template<typename T>
void  printAll(std::vector<T> const & v, ft::vector<T> const & ft_v) {
  printStdVec<T>(v);
  printMyVec<T>(ft_v);
  printStdVecSize<T>(v);
  printMyVecSize<T>(ft_v);
  printStdVecCap<T>(v);
  printMyVecCap<T>(ft_v);
}
