//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//          In preparing these files, several sources were          //
//            consulted, they are listed in no particular           //
//                          order below.                            //
//                                                                  //
//  Source: https://github.com/Ekan5h/AVLtree                       //
//  Author: Ekansh Mahendru                                         //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3TREE_H_
#define _H3TREE_H_

#pragma once

#include "H3Base.h"

// * forward declaration
template <typename Type> class H3Tree;

template <typename Type>
class H3Node
{
public:
	friend class H3Tree<Type>;
	Type& GetData() { return m_data; }
	Type* GetDataPtr() { return &m_data; }

	H3Node(Type &t) :
		m_data(t),
		m_height(1)
	{
		m_left = nullptr;
		m_right = nullptr;
	}

private:
	Type m_data;
	INT m_height;
	H3Node<Type>* m_left;
	H3Node<Type>* m_right;
};

template <typename Type>
class H3Tree
{
	typedef int(__stdcall *CompFunc) (const Type& new_node, const Type& existing_node);

	H3Node<Type>* m_root;
	INT m_count;
	const CompFunc m_compare;
#ifndef CPLUSPLUS11
	H3Tree();
#endif

	INT _Height(H3Node<Type>* node);
	H3Node<Type>* _RotateRight(H3Node<Type>* node);
	H3Node<Type>* _RotateLeft(H3Node<Type>* node);
	const H3Node<Type>* _Search(H3Node<Type>* root, Type& t) const;
	H3Node<Type>* _Insert(H3Node<Type>* root, Type& t, Type* result);
	H3Node<Type>* _Remove(H3Node<Type>* root, Type& t);
	VOID _Delete(H3Node<Type>* root);
	VOID _Inorder(H3Node<Type>* root, H3Vector<Type>& vector);

public:
#ifdef CPLUSPLUS11
	H3Tree() = delete; // this should not be used!
#endif
	H3Tree(CompFunc TypeComparison) :
		m_count(0),
		m_compare(TypeComparison)
	{
		m_root = nullptr;
	}
	~H3Tree() { _Delete(m_root); }
	Type* Insert(Type& t);
	VOID Remove(Type& t);
	INT Count() const { return m_count; }
	const Type* Find(Type& t) const;
	H3Vector<Type> OrderedTravel();
};

template<typename Type>
inline INT H3Tree<Type>::_Height(H3Node<Type>* node)
{
	if (node == nullptr)
		return 0;
	return node->m_height;
}

template<typename Type>
inline H3Node<Type>* H3Tree<Type>::_RotateRight(H3Node<Type>* node)
{
	H3Node<Type>* root = node->m_left;
	node->m_left = root->m_right;
	root->m_right = node;
	node->m_height = 1 + std::max(_Height(node->m_left), _Height(node->m_right));
	root->m_height = 1 + std::max(_Height(root->m_left), _Height(root->m_right));
	return root;
}

template<typename Type>
inline H3Node<Type>* H3Tree<Type>::_RotateLeft(H3Node<Type>* node)
{
	H3Node<Type>* root = node->m_right;
	node->m_right = root->m_left;
	root->m_left = node;
	node->m_height = 1 + std::max(_Height(node->m_left), _Height(node->m_right));
	root->m_height = 1 + std::max(_Height(root->m_left), _Height(root->m_right));
	return root;
}

template<typename Type>
inline const H3Node<Type>* H3Tree<Type>::_Search(H3Node<Type>* root, Type & t) const
{
	if (root == nullptr)
		return nullptr;
	int comparison = m_compare(t, root->m_data);
	if (comparison == 0)
		return root;
	if (comparison < 0)
		return _Search(root->m_left, t);
	else
		return _Search(root->m_right, t);
}

template<typename Type>
inline H3Node<Type>* H3Tree<Type>::_Insert(H3Node<Type>* root, Type & t, Type* result)
{
	if (root == nullptr)
	{
		++m_count;
		H3Node<Type>* new_node = new H3Node<Type>(t);
		result = &new_node->m_data;
		return new_node;
	}

	int comparison = m_compare(t, root->m_data);
	if (comparison < 0)
		root->m_left = _Insert(root->m_left, t, result);
	else if (comparison > 0)
		root->m_right = _Insert(root->m_right, t, result);
	else // (comparison == 0) --> no insertion, no re-ordering
	{
		result = &root->m_data;
		return root;
	}

	int height_left = _Height(root->m_left);
	int height_right = _Height(root->m_right);

	root->m_height = 1 + std::max(height_left, height_right);

	int balance = height_left - height_right;

	if (balance > 1)
	{
		int left_compare = m_compare(t, root->m_left->m_data);
		if (left_compare < 0)
			return _RotateRight(root);
		else
		{
			root->m_left = _RotateLeft(root->m_left);
			return _RotateRight(root);
		}
	}
	else if (balance < -1)
	{
		int right_compare = m_compare(t, root->m_right->m_data);
		if (right_compare > 0)
			return _RotateLeft(root);
		else
		{
			root->m_right = _RotateRight(root->m_right);
			return _RotateLeft(root);
		}
	}

	return root;
}

template<typename Type>
inline H3Node<Type>* H3Tree<Type>::_Remove(H3Node<Type>* root, Type & t)
{
	if (root == nullptr)
		return nullptr;

	int comparison = m_compare(t, root->m_data);
	if (comparison < 0)
		root->m_left = _Remove(root->m_left, t);
	else if (comparison > 0)
		root->m_right = _Remove(root->m_right, t);
	else // == 0
	{
		H3Node<Type>* right = root->m_right;
		if (right == nullptr)
		{
			H3Node<Type>* left = root->m_left;
			delete root;
			root = left;
		}
		else if (root->m_left == nullptr)
		{
			delete root;
			root = right;
		}
		else
		{
			while (right->m_left != nullptr)
				right = right->m_left;
			root->m_data(right->m_data);
			root->m_right = _Remove(root->m_right, right->m_data);
		}
	}

	if (root == nullptr)
		return root;

	int height_left = _Height(root->m_left);
	int height_right = _Height(root->m_right);
	int balance = height_left - height_right;

	if (balance > 1)
	{
		int left_compare = m_compare(t, root->m_left->m_data);
		if (left_compare > 0)
			return _RotateRight(root);

		root->m_left = _RotateLeft(root->m_left);
		return _RotateRight(root);
	}
	if (balance < -1)
	{
		int right_compare = m_compare(t, root->m_right->m_data);
		if (right_compare < 0)
			return _RotateLeft(root);

		root->m_right = _RotateRight(root->m_right);
		return _RotateLeft(root);
	}

	return root;
}

template<typename Type>
inline VOID H3Tree<Type>::_Delete(H3Node<Type>* root)
{
	if (root == nullptr)
		return;
	_Delete(root->m_left);
	_Delete(root->m_right);
	delete root;
}

template<typename Type>
inline VOID H3Tree<Type>::_Inorder(H3Node<Type>* root, H3Vector<Type>& vector)
{
	if (root == nullptr)
		return;
	_Inorder(root->m_left, vector);
	vector.Add(root->GetData());
	_Inorder(root->m_right, vector);
}

template<typename Type>
inline Type* H3Tree<Type>::Insert(Type & t)
{
	Type* result = nullptr;
	m_root = _Insert(m_root, t, result);
	return result;
}

template<typename Type>
inline VOID H3Tree<Type>::Remove(Type & t)
{
	m_root = _Remove(m_root, t);
}

template<typename Type>
inline const Type * H3Tree<Type>::Find(Type & t) const
{
	const H3Node<Type>* f = _Search(m_root, t);
	if (f == nullptr)
		return nullptr;
	return &f->m_data;
}

template<typename Type>
inline H3Vector<Type> H3Tree<Type>::OrderedTravel()
{
	H3Vector<Type> nodes;

	_Inorder(m_root, nodes);

	return nodes;
}

#endif // #define _H3TREE_H_