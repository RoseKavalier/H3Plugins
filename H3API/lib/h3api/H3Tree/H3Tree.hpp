//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3TREE_HPP_
#define _H3TREE_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_Vector.hpp"

namespace h3
{
	// * forward declaration
	template <typename Type> 
	class H3Tree;

	template <typename Type>
	class H3Node
	{
	public:
		friend class H3Tree<Type>;
		Type& GetData();
		Type* GetDataPtr();
		H3Node(Type& t);
	private:
		Type m_data;
		INT m_height;
		H3Node<Type>* m_left;
		H3Node<Type>* m_right;
	};

	template <typename Type>
	class H3Tree
	{
		typedef int(__stdcall* CompFunc) (const Type& new_node, const Type& existing_node);

		H3Node<Type>* m_root;
		INT m_count;
		const CompFunc m_compare;
#ifndef _CPLUSPLUS11_
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
#ifdef _CPLUSPLUS11_
		H3Tree() = delete; // this should not be used!
#endif
		H3Tree(CompFunc TypeComparison);
		~H3Tree();
		Type* Insert(Type& t);
		VOID Remove(Type& t);
		INT Count() const;
		const Type* Find(Type& t) const;
		H3Vector<Type> OrderedTravel();
	};
}

#endif /* #define _H3TREE_HPP_ */