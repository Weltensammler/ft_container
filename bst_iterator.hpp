/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguth <tguth@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:13 by ben               #+#    #+#             */
/*   Updated: 2023/02/04 10:31:41 by tguth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP


#include "iterator.hpp"
#include "bst.hpp"

namespace ft
{

	template<class node, class _value_type>
	class tree_iterator
	{
		public:
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef _value_type									value_type;
			typedef _value_type*								pointer;
			typedef _value_type&								reference;
			typedef std::ptrdiff_t								difference_type;


			node*												current_node;


		
			tree_iterator() : current_node()
			{}

			explicit tree_iterator (node* node_) : current_node(node_)
			{}
			
			tree_iterator (const tree_iterator<node, _value_type>& rev_it) : current_node(rev_it.current_node)
			{}

			template <class U>
			tree_iterator (const tree_iterator<node, U>& rev_it) : current_node(rev_it.current_node)
			{}

			tree_iterator& operator=(const tree_iterator<node, _value_type>& rev_it)
			{
				current_node = rev_it.current_node;
				return (*this);
			}
			
			tree_iterator operator ++ (int)         
			{
				tree_iterator tmp(*this);
				++*this;
				return tmp;
			}

			tree_iterator& operator ++ ()       
			{
				if (current_node->right && current_node->right->left)
				{
					current_node = current_node->right;
					while (current_node->left->left)
						current_node = current_node->left;
				}
				else
				{
					node* t = current_node;
					while (current_node && current_node->p && current_node != current_node->p->left)
					{
						current_node = current_node->p;
					}
					if (!current_node->p)
						current_node = t->right;
					else
						current_node = current_node->p;
					
				}
				return *this;
			}

			tree_iterator& operator -- ()              
			{
				if (current_node->left && current_node->left->left)
				{
					current_node = current_node->left;
					while (current_node->right->left)
						current_node = current_node->right;
				}
				else
				{
					node* t = current_node;
					while (current_node && current_node->p && current_node != current_node->p->right)
					{
						current_node = current_node->p;
					}
					if (!current_node->p)
						current_node = t->left;
					else
						current_node = current_node->p;
				}
				return *this;
			}

			tree_iterator operator -- (int)              
			{
				tree_iterator tmp(*this);
				--*this;
				return tmp;
			}
	
			reference operator*() const 
			{
				pointer tmp = &(*current_node).data;
				return *(tmp);
			}
			pointer operator->() const 
			{
				return &(*current_node).data;
			}
	};
	
	template<class node, class _value_type, class constval>
	bool operator==( const ft::tree_iterator<node, _value_type>& lhs,
                 const ft::tree_iterator<node, constval>& rhs )   
	{
		if (lhs.current_node != rhs.current_node)
			return false;
		return true;
	}

	template<class node, class _value_type, class constval>
	bool operator!=( const ft::tree_iterator<node, _value_type>& lhs,
                 const ft::tree_iterator<node, constval>& rhs )   
	{
		if (lhs.current_node == rhs.current_node)
			return false;
		return true;
	}
}

#endif