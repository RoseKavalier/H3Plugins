//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-08-13                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3SET_INL_
#define _H3SET_INL_

#include "H3Set.hpp"

namespace h3
{
	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::Node* H3Set<T, NilNode>::head() const
	{
		return m_root->parent;
	}
	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::NodePtr H3Set<T, NilNode>::Nil() const
	{
		return NodePtr(PtrAt(NilNode));
	}

	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::iterator H3Set<T, NilNode>::begin()
	{
		return iterator(m_root->left);
	}
	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::iterator H3Set<T, NilNode>::begin() const
	{
		return iterator(m_root->left);
	}

	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::iterator H3Set<T, NilNode>::end()
	{
		return iterator(m_root);
	}
	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::iterator H3Set<T, NilNode>::end() const
	{
		return iterator(m_root);
	}

	template<typename T, UINT NilNode>
	inline UINT H3Set<T, NilNode>::Count() const
	{
		return m_count;
	}

	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::iterator H3Set<T, NilNode>::Find(const T& key) const
	{
		NodePtr end_node = NodePtr(PtrAt(NilNode));
		NodePtr it = head();
		NodePtr result = m_root;
		while (it != end_node)
		{
			if (it->data < key)
				it = it->right;
			else
			{
				result = it;
				it = it->left;
			}
		}
		if (result == end_node)
			return end();
		if (key < result->data)
			return end();
		return iterator(result);
	}

	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::Node* H3Set<T, NilNode>::iterator::endNode() const
	{
		return NodePtr(PtrAt(NilNode));
	}

	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::iterator& H3Set<T, NilNode>::iterator::operator++()
	{
		NodePtr end_node = endNode();
		NodePtr node = m_node->right;
		if (node != end_node)
		{
			while (node->left != end_node) // min
				node = node->left;
			m_node = node;
		}
		else
		{
			NodePtr parent = m_node->parent;
			while (parent->right == m_node)
			{
				m_node = parent;
				parent = m_node->parent;
			}
			if (m_node->right != parent)
				m_node = parent;
		}
		return *this;
	}

	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::iterator H3Set<T, NilNode>::iterator::operator++(int)
	{
		iterator it(m_node);
		++(*this);
		return it;
	}

	template<typename T, UINT NilNode>
	inline T& H3Set<T, NilNode>::iterator::operator*() const
	{
		return m_node->data;
	}

	template<typename T, UINT NilNode>
	inline T* H3Set<T, NilNode>::iterator::operator->() const
	{
		return &m_node->data;
	}

	template<typename T, UINT NilNode>
	inline bool H3Set<T, NilNode>::iterator::operator==(const iterator& it) const
	{
		return m_node == it.m_node;
	}

	template<typename T, UINT NilNode>
	inline bool H3Set<T, NilNode>::iterator::operator!=(const iterator& it) const
	{
		return m_node != it.m_node;
	}

	template<typename T, UINT NilNode>
	inline H3Set<T, NilNode>::iterator::iterator(NodePtr node) :
		m_node(node)
	{
	}

	template<typename T, UINT NilNode>
	inline typename H3Set<T, NilNode>::Node* H3Set<T, NilNode>::iterator::Get() const
	{
		return m_node;
	}
}

#endif /* #define _H3SET_INL_ */