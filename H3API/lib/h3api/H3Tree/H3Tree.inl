//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3TREE_INL_
#define _H3TREE_INL_

#include "H3Tree.hpp"

namespace h3
{
	template<typename T>
	inline H3Tree<T>::H3Node::H3Node() :
		m_data(), m_black(true), m_parent(), m_left(), m_right()
	{
	}

	template<typename T>
	inline H3Tree<T>::H3Node::H3Node(const T& data) :
		m_data(data), m_black(true), m_parent(), m_left(), m_right()
	{
	}

	template<typename T>
	inline typename H3Tree<T>::H3Node* H3Tree<T>::H3Node::Next()
	{
		H3Node* node;
		if (node = m_right)
		{
			while (node->m_left)
				node = node->m_left;
			return node;
		}
		node = this;
		H3Node* parent = m_parent;
		while (parent->m_left != node)
		{
			node = parent;
			parent = node->m_parent;
		}
		return parent;
	}

	template<typename T>
	inline typename H3Tree<T>::H3Node* H3Tree<T>::H3Node::Previous()
	{
		H3Node* node;
		if (node = m_left)
		{
			while (node->m_right)
				node = node->m_right;
			return node;
		}
		node = this;
		H3Node* parent = node->m_parent;
		while (parent->m_right != node)
		{
			node = parent;
			parent = node->m_parent;
		}
		return parent;
	}

	template<typename T>
	inline typename H3Tree<T>::H3Node* H3Tree<T>::H3Node::LeftMost()
	{
		H3Node* node = this;
		while (node->m_left)
			node = node->m_left;
		return node;
	}

	template<typename T>
	inline typename H3Tree<T>::iterator& H3Tree<T>::iterator::operator++()
	{
		m_ptr = m_ptr->Next();
		return *this;
	}

	template<typename T>
	inline typename H3Tree<T>::iterator H3Tree<T>::iterator::operator++(int)
	{
		iterator it(m_ptr);
		m_ptr = m_ptr->Next();
		return it;
	}

	template<typename T>
	inline typename H3Tree<T>::iterator& H3Tree<T>::iterator::operator--()
	{
		m_ptr = m_ptr->Previous();
		return *this;
	}

	template<typename T>
	inline typename H3Tree<T>::iterator H3Tree<T>::iterator::operator--(int)
	{
		iterator it(m_ptr);
		m_ptr = m_ptr->Previous();
		return it;
	}

	template<typename T>
	inline typename T& H3Tree<T>::iterator::operator*() const
	{
		return m_ptr->m_data;
	}

	template<typename T>
	inline typename T* H3Tree<T>::iterator::operator->() const
	{
		return &m_ptr->m_data;
	}

	template<typename T>
	inline bool H3Tree<T>::iterator::operator==(const iterator& it) const
	{
		return m_ptr == it.m_ptr;
	}

	template<typename T>
	inline bool H3Tree<T>::iterator::operator!=(const iterator& it) const
	{
		return m_ptr != it.m_ptr;
	}

	template<typename T>
	inline H3Tree<T>::iterator::iterator(H3Node* node) :
		m_ptr(node)
	{
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator& h3::H3Tree<T>::const_iterator::operator++()
	{
		m_ptr = next(m_ptr);
		return *this;
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator H3Tree<T>::const_iterator::operator++(int)
	{
		const_iterator it(m_ptr);
		m_ptr = next(m_ptr);
		return it;
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator& H3Tree<T>::const_iterator::operator--()
	{
		m_ptr = previous(m_ptr);
		return *this;
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator H3Tree<T>::const_iterator::operator--(int)
	{
		const_iterator it(m_ptr);
		m_ptr = previous(m_ptr);
		return it;
	}

	template<typename T>
	inline const T& H3Tree<T>::const_iterator::operator*() const
	{
		return m_ptr->m_data;
	}

	template<typename T>
	inline const T* H3Tree<T>::const_iterator::operator->() const
	{
		return &m_ptr->m_data;
	}

	template<typename T>
	inline bool H3Tree<T>::const_iterator::operator==(const const_iterator& it) const
	{
		return m_ptr == it.m_ptr;
	}

	template<typename T>
	inline bool H3Tree<T>::const_iterator::operator!=(const const_iterator& it) const
	{
		return m_ptr != it.m_ptr;
	}

	template<typename T>
	inline H3Tree<T>::const_iterator::const_iterator(H3Node* node) :
		m_ptr(node)
	{
	}

	template<typename T>
	inline H3Tree<T>::H3Tree() :
		m_anchor(), m_begin(m_end), m_end(&m_anchor), m_size(0)
	{
		m_anchor.m_parent = m_end;
	}

	template<typename T>
	inline H3Tree<T>::~H3Tree()
	{
		Clear();
	}

	template<typename T>
	inline typename H3Tree<T>::iterator H3Tree<T>::begin()
	{
		return iterator(m_begin);
	}

	template<typename T>
	inline typename H3Tree<T>::iterator H3Tree<T>::end()
	{
		return iterator(m_end);
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator H3Tree<T>::begin() const
	{
		return const_iterator(m_begin);
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator H3Tree<T>::end() const
	{
		return const_iterator(m_end);
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator H3Tree<T>::cbegin() const
	{
		return const_iterator(m_begin);
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator H3Tree<T>::cend() const
	{
		return const_iterator(m_end);
	}

	template<typename T>
	inline void H3Tree<T>::Clear()
	{
		for (H3Node* it = m_begin; it != m_end; )
		{
			H3Node* curr = it;
			it = it->Next();
			delete curr;
		}

		m_size = 0;
		m_begin = m_end;
		m_end = &m_anchor;
		m_anchor.m_parent = m_end;
	}

	template<typename T>
	inline bool H3Tree<T>::Insert(const T& data)
	{
		return insert(data);
	}

	template<typename T>
	inline bool H3Tree<T>::Erase(const T& data)
	{
		return erase(data);
	}

	template<typename T>
	inline bool H3Tree<T>::Erase(iterator& it)
	{
		return erase(it);
	}

	template<typename T>
	inline typename H3Tree<T>::iterator H3Tree<T>::Find(const T& data)
	{
		return iterator(find(data));
	}

	template<typename T>
	inline typename H3Tree<T>::const_iterator H3Tree<T>::Find(const T& data) const
	{
		return const_iterator(find(data));
	}

	template<typename T>
	inline UINT H3Tree<T>::Size() const
	{
		return m_size;
	}

	template<typename T>
	inline typename H3Tree<T>::H3Node* H3Tree<T>::find(const T& data)
	{
		H3Node* root = m_end;
		H3Node* node = m_end->m_left;

		while (node)
		{
			if (node->m_data < data)
				node = node->m_right;
			else
			{
				root = node;
				node = node->m_left;
			}
		}

		if (root == m_end || data < root->m_data)
			return m_end;
		return root;
	}

	template<typename T>
	inline bool H3Tree<T>::erase(const T& data)
	{
		return erase(find(data));
	}

	template<typename T>
	inline bool H3Tree<T>::erase(iterator& it)
	{
		if (it == end())
			return false;

		H3Node* node = it.m_ptr;
		H3Node* root;
		H3Node* parent;
		H3Node* temp = node;
		bool yblack = temp->m_black;

		if (!node->m_left)
		{
			root = node->m_right;
			if (node == m_begin)
				m_begin = node->Next();
			insertAt(node, node->m_right);
			parent = temp->m_parent;
		}
		else if (!node->m_right)
		{
			root = node->m_left;
			insertAt(node, node->m_left);
			parent = temp->m_parent;
		}
		else
		{
			temp = node->LeftMost();
			yblack = temp->m_black;
			root = temp->m_right;
			if (temp->m_parent != node)
			{
				insertAt(temp, temp->m_right);
				temp->m_right = node->m_right;
				temp->m_right->m_parent = temp;
				parent = temp->m_parent;
			}
			else
				parent = temp;
			insertAt(node, temp);
			temp->m_left = node->m_left;
			temp->m_left->m_parent = temp;
			temp->m_black = node->m_black;
		}

		if (yblack)
			erasureBalance(root, parent);

		--m_size;
		delete node;
	}

	template<typename T>
	inline bool H3Tree<T>::insert(const T& data)
	{
		H3Node* left = m_end->m_left;
		H3Node* node = m_end;
		bool is_smaller = true;
		while (left)
		{
			node = left;
			is_smaller = data < left->m_data;
			left = is_smaller ? left->m_left : left->m_right;
		}

		H3Node* right = node;
		if (is_smaller) // left
		{
			if (node == m_end) // tree is empty, set new root
			{
				H3Node* new_node = new H3Node(data);
				++m_size;
				m_begin = new_node;
				m_end->m_left = new_node;
				m_end->m_right = new_node;
				new_node->m_parent = m_end;
				insertionBalance(new_node);
				return true;
			}
			else if (node == m_begin)
			{
				H3Node* new_node = new H3Node(data);
				++m_size;

				m_begin = new_node;
				node->m_left = new_node;
				new_node->m_parent = node;

				insertionBalance(new_node);
				return true;
			}
			else
			{
				H3Node* parent = right->m_parent;
				while (right != parent->m_right)
				{
					right = parent;
					parent = right->m_parent;
				}
				right = parent;

				if (right->m_data < data)
				{
					H3Node* new_node = new H3Node(data);
					++m_size;

					node->m_left = new_node;
					new_node->m_parent = node;

					insertionBalance(new_node);
					return true;
				}
				// * duplicate
				return false;
			}
		}

		if (right->m_data < data)
		{
			H3Node* new_node = new H3Node(data);
			++m_size;
			node->m_right = new_node;
			new_node->m_parent = node;
			insertionBalance(new_node);
			return true;
		}
		// * duplicate
		return false;
	}

	template<typename T>
	inline void H3Tree<T>::insertionBalance(H3Node* node)
	{
		H3Node* uncle;

		node->m_black = false;

		while (!node->m_parent->m_black)
		{
			if (node->m_parent == node->m_parent->m_parent->m_left)
			{
				uncle = node->m_parent->m_parent->m_right;

				if (uncle && !uncle->m_black)
				{
					node->m_parent->m_black = true;
					uncle->m_black = true;
					node->m_parent->m_parent->m_black = false;
					node = node->m_parent->m_parent;
				}
				else {
					if (node == node->m_parent->m_right)
					{
						node = node->m_parent;
						rotateLeft(node);
					}
					node->m_parent->m_black = true;
					node->m_parent->m_parent->m_black = false;

					rotateRight(node->m_parent->m_parent);
				}
			}
			else {
				uncle = node->m_parent->m_parent->m_left;
				if (uncle && !uncle->m_black)
				{
					node->m_parent->m_black = true;
					uncle->m_black = true;
					node->m_parent->m_parent->m_black = false;
					node = node->m_parent->m_parent;
				}
				else
				{
					if (node == node->m_parent->m_left)
					{
						node = node->m_parent;
						rotateRight(node);
					}
					node->m_parent->m_black = true;
					node->m_parent->m_parent->m_black = false;

					rotateLeft(node->m_parent->m_parent);
				}
			}
		}
		m_end->m_left->m_black = true;
	}

	template<typename T>
	inline void H3Tree<T>::erasureBalance(H3Node* node, H3Node* parent)
	{
		while (node != m_end->m_left && (!node || node->m_black))
		{
			if (node == parent->m_left)
			{
				H3Node* sibling = parent->m_right;
				if (!sibling->m_black)
				{
					sibling->m_black = true;
					parent->m_black = false;
					rotateLeft(parent);
					sibling = parent->m_right;
				}
				if ((!sibling->m_left || sibling->m_left->m_black) && (!sibling->m_right || sibling->m_right->m_black))
				{
					sibling->m_black = false;
					node = parent;
					parent = parent->m_parent;
				}
				else {
					if (!sibling->m_right|| sibling->m_right->m_black)
					{
						if (sibling->m_left)
							sibling->m_left->m_black = true;
						sibling->m_black = false;
						rotateRight(sibling);
						sibling = parent->m_right;
					}
					sibling->m_black = parent->m_black;
					parent->m_black = true;
					if (sibling->m_right)
						sibling->m_right->m_black = true;
					rotateLeft(parent);
					node = m_end->m_left;
				}
			}
			else {
				H3Node* sibling = parent->m_left;
				if (!sibling->m_black)
				{
					sibling->m_black = true;
					parent->m_black = false;
					rotateRight(parent);
					sibling = parent->m_left;
				}
				if ((!sibling->m_left || sibling->m_left->m_black) && (!sibling->m_right || sibling->m_right->m_black))
				{
					sibling->m_black = false;
					node = parent;
					parent = parent->m_parent;
				}
				else
				{
					if (!sibling->m_left || sibling->m_left->m_black)
					{
						if (sibling->m_right)
							sibling->m_right->m_black = true;
						sibling->m_black = false;
						rotateLeft(sibling);
						sibling = parent->m_left;
					}
					sibling->m_black = parent->m_black;
					parent->m_black = true;
					if (sibling->m_left)
						sibling->m_left->m_black = true;
					rotateRight(parent);
					node = m_end->m_left;
				}
			}
		}
		if (node)
			node->m_black = true;
	}

	template<typename T>
	inline void H3Tree<T>::rotateLeft(H3Node* node)
	{
		H3Node* tmp = node->m_right;

		node->m_right = tmp->m_left;
		if (tmp->m_left)
			tmp->m_left->m_parent = node;

		tmp->m_parent = node->m_parent;

		if (node->m_parent == m_end)
		{
			m_end->m_left = tmp;
			m_end->m_right = tmp;
			tmp->m_parent = m_end;
		}
		else if (node == node->m_parent->m_left)
			node->m_parent->m_left = tmp;
		else
			node->m_parent->m_right = tmp;

		tmp->m_left = node;
		node->m_parent = tmp;
	}

	template<typename T>
	inline void H3Tree<T>::rotateRight(H3Node* node)
	{
		H3Node* tmp = node->m_left;
		node->m_left = tmp->m_right;
		if (tmp->m_right)
			tmp->m_right->m_parent = node;

		tmp->m_parent = node->m_parent;
		if (node->m_parent == m_end)
		{
			m_end->m_left = tmp;
			m_end->m_right = tmp;
			tmp->m_parent = m_end;
		}
		else if (node == node->m_parent->m_right)
			node->m_parent->m_right = tmp;
		else
			node->m_parent->m_left = tmp;

		tmp->m_right = node;
		node->m_parent = tmp;
	}

	template<typename T>
	inline void H3Tree<T>::insertAt(H3Node* dst, H3Node* node)
	{
		if (dst->m_parent == m_end)
		{
			m_end->m_left = node;
			m_end->m_right = node;
		}
		else if (dst == dst->m_parent->m_left)
			dst->m_parent->m_left = node;
		else
			dst->m_parent->m_right = node;

		if (node)
			node->m_parent = dst->m_parent;
	}
}

#endif /* #define _H3TREE_INL_ */