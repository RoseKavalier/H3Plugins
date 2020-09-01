//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-08-13                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3SET_HPP_
#define _H3SET_HPP_

#include "../H3_Base.hpp"

namespace h3
{
#pragma pack(push, 4)
    /**
     * @brief A representation of std::set as found within h3
     * @tparam T Stored elements with comparison int operator<(const&)
     * @tparam NilNode The address of the static nil node
     */
    template<typename T, UINT NilNode = 0>
    struct H3Set
    {
        struct Node
        {
            Node* left;    /**< @brief [00] left child*/
            Node* parent;  /**< @brief [04] parent node*/
            Node* right;   /**< @brief [08] right child*/
            T     data;    /**< @brief [0C] The data for this node*/
            BOOL  isBlack; /**< @brief [0C + sizeof(T)] whether the node is black(1) or red(0)*/

            T* operator->() const { return &data; }
            T& operator*() const  { return data; }
        };
        typedef typename Node* NodePtr;
    protected:
        h3unk8 _allocator;  /**< @brief [00] default allocator, C++ requires 1 byte even if no body*/
        h3unk8 _keyCompare; /**< @brief [01] default key comparator, C++ requires 1 byte even if no body*/
        Node*  m_root;      /**< @brief [04] The anchor node of the tree*/
        BOOL8  m_multiset;  /**< @brief [08] accept duplicate keys or not*/
        UINT32 m_count;     /**< @brief [0C] The number of nodes in the tree*/

        Node* head() const;

        static constexpr Node** _Nil = reinterpret_cast<Node**>(NilNode);
    public:

        /**
         * @brief An iterator to go over H3Set
         */
        struct iterator
        {
        protected:
            Node* m_node;
            Node* endNode() const;
        public:
            iterator& operator++();
            iterator operator++(int);
            T& operator*() const;
            T* operator->() const;
            bool operator==(const iterator& it) const;
            bool operator!=(const iterator& it) const;
            iterator(NodePtr node);
            Node* Get() const;
        };
        iterator begin();
        iterator begin() const;
        iterator end();
        iterator end() const;

        /**
         * @brief Obtains the static nil node from its templated address
         * @return NodePtr nil node
        */
        NodePtr  Nil() const;
        /**
         * @brief The number of nodes currently residing in the set
         * @return 0...n nodes
        */
        UINT Count() const;
        /**
         * @brief Finds matching data to the specified key within the set
         * @param key A key to the data to find
         * @return An iterator to the matching object if found, otherwise to end() iterator
        */
        iterator Find(const T& key) const;

        // Insert is not provided, specialized sets can have it (e.g. Resource Manager)
    };
    _H3API_ASSERT_SIZE_(H3Set<h3unk>, 0x10);
#pragma pack(pop)
}

#endif /* #define _H3SET_HPP_ */