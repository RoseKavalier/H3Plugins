//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3TREE_HPP_
#define _H3TREE_HPP_

#include "../H3_Base.hpp"
#include "../H3_Vector.hpp"

namespace h3
{
	// * Red-black tree with iterators
	// * value type T requires comparison bool operator<(const T&)
	template<typename T>
	class H3Tree
	{
	private:
		class H3Node : public H3Allocator
		{
			friend class H3Tree;

			H3Node*    m_left;
			H3Node*    m_parent;
			H3Node*    m_right;
			T          m_data;
			bool       m_black;

			H3Node* Next();
			H3Node* Previous();
			H3Node* LeftMost();

		public:
			H3Node();
			H3Node(const T& data);
		};

		H3Node  m_anchor;
		H3Node* m_begin;
		H3Node* m_end;
		UINT    m_size;

	public:
		class iterator
		{
			friend class H3Tree;
		public:
			iterator& operator++();
			iterator operator++(int);
			iterator& operator--();
			iterator operator--(int);
			T& operator*() const;
			T* operator->() const;
			bool operator==(const iterator& it) const;
			bool operator!=(const iterator& it) const;
			iterator(H3Node* node);
		private:
			H3Node* m_ptr;
		};
		class const_iterator
		{
			friend class H3Tree;
		public:
			const_iterator& operator++();
			const_iterator operator++(int);
			const_iterator& operator--();
			const_iterator operator--(int);
			const T& operator*() const;
			const T* operator->() const;
			bool operator==(const const_iterator& it) const;
			bool operator!=(const const_iterator& it) const;
			const_iterator(H3Node* node);
		private:
			H3Node* m_ptr;
		};

		H3Tree();
		~H3Tree();
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
		void Clear();
		bool Insert(const T& data);
		bool Erase(const T& data);
		bool Erase(iterator& it);
		iterator Find(const T& data);
		const_iterator Find(const T& data) const;
		UINT Size() const;

	private:
		H3Node* find(const T& data);
		bool erase(const T& data);
		bool erase(iterator& it);
		bool insert(const T& data);
		void insertionBalance(H3Node* node);
		void erasureBalance(H3Node* node, H3Node* parent);
		void rotateLeft(H3Node* node);
		void rotateRight(H3Node* node);
		void insertAt(H3Node* dst, H3Node* src);
	};
}

#endif /* #define _H3TREE_HPP_ */