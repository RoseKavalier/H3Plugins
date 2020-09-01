//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BASE_INL_
#define _H3BASE_INL_

#include "H3Base.hpp"

namespace h3
{
	template<typename T>
	inline H3Map<T>::iterator::iterator(const iterator& it) :
		m_current(it.m_current),
		m_x(it.m_x),
		m_y(it.m_y),
		m_z(it.m_z),
		m_map(it.m_map)
	{
	}
	template<typename T>
	inline H3Map<T>::iterator::iterator(H3Map* map, UINT x, UINT y, UINT z) :
		m_current(map->at(x, y, z)),
		m_x(x),
		m_y(y),
		m_z(z),
		m_map(map)
	{
	}
	template<typename T>
	inline H3Map<T>::iterator::iterator(H3Map* map, pointer item) :
		m_current(item),
		m_map(map)
	{
		UINT delta = item - map->m_base;
		m_x = delta % map->m_dimensions;
		delta /= map->m_dimensions;
		m_y = delta % map->m_dimensions;
		m_z = delta / map->m_dimensions;
	}
	template<typename T>
	inline BOOL H3Map<T>::iterator::operator==(const iterator& it) const
	{
		return m_current == it.m_current;
	}
	template<typename T>
	inline BOOL H3Map<T>::iterator::operator!=(const iterator& it) const
	{
		return m_current != it.m_current;
	}
	template<typename T>
	inline typename H3Map<T>::iterator& H3Map<T>::iterator::operator++()
	{
		++m_current;
		if (++m_x < m_map->m_dimensions)
			return *this;
		m_x = 0;
		if (++m_y < m_map->m_dimensions)
			return *this;
		m_y = 0;
		++m_z;
		return *this;
	}
	template<typename T>
	inline typename H3Map<T>::iterator H3Map<T>::iterator::operator++(int)
	{
		iterator it(*this);
		++(*this);
		return it;
	}
	template<typename T>
	inline typename H3Map<T>::pointer H3Map<T>::iterator::operator->() const
	{
		return m_current;
	}
	template<typename T>
	inline typename H3Map<T>::pointer H3Map<T>::iterator::operator&() const
	{
		return m_current;
	}
	template<typename T>
	inline typename H3Map<T>::reference H3Map<T>::iterator::operator*() const
	{
		return *m_current;
	}
	template<typename T>
	inline typename H3Map<T>::reference H3Map<T>::iterator::operator()(INT dx, INT dy) const
	{
		return m_current[dx + m_map->m_dimensions * dy];
	}
	template<typename T>
	inline UINT H3Map<T>::iterator::GetX() const
	{
		return m_x;
	}
	template<typename T>
	inline UINT H3Map<T>::iterator::GetY() const
	{
		return m_y;
	}
	template<typename T>
	inline UINT H3Map<T>::iterator::GetZ() const
	{
		return m_z;
	}
	template<typename T>
	inline H3Point H3Map<T>::iterator::Get() const
	{
		return H3Point(m_x, m_y, m_z);
	}
	template<typename T>
	inline typename H3Map<T>::iterator H3Map<T>::begin()
	{
		return iterator(this, 0, 0, 0);
	}
	template<typename T>
	inline typename H3Map<T>::iterator H3Map<T>::end()
	{
		return iterator(this, 0, 0, m_levels);
	}
	template<typename T>
	inline typename H3Map<T>::iterator H3Map<T>::operator()(UINT x, UINT y, UINT z)
	{
		return iterator(this, x, y, z);
	}
	template<typename T>
	inline H3Map<T>::H3Map(pointer base, UINT map_size, BOOL has_underground) :
		m_base(base),
		m_dimensions(map_size),
		m_levels(has_underground ? 2 : 1)
	{
	}
	template<typename T>
	inline typename H3Map<T>::reference H3Map<T>::At(UINT x, UINT y, UINT z)
	{
		return *at(x, y, z);
	}
	template<typename T>
	inline typename H3Map<T>::pointer H3Map<T>::at(UINT x, UINT y, UINT z)
	{
		return &m_base[x + m_dimensions * (y + z * m_dimensions)];
	}

	template<typename T>
	inline BOOL H3FastMap<T>::iterator::operator==(const iterator& it) const
	{
		return m_current == it.m_current;
	}

	template<typename T>
	inline BOOL H3FastMap<T>::iterator::operator!=(const iterator& it) const
	{
		return m_current != it.m_current;
	}

	template<typename T>
	inline typename H3FastMap<T>::iterator& H3FastMap<T>::iterator::operator++()
	{
		++m_current;
		return *this;
	}

	template<typename T>
	inline typename H3FastMap<T>::iterator H3FastMap<T>::iterator::operator++(int)
	{
		iterator it(*this);
		++m_current;
		return it;
	}

	template<typename T>
	inline typename H3FastMap<T>::reference H3FastMap<T>::iterator::operator()(INT dx, INT dy) const
	{
		return m_current[dx + m_dimensions * dy];
	}

	template<typename T>
	inline H3FastMap<T>::iterator::iterator(const iterator& it) :
		m_current(it.m_current),
		m_dimensions(it.m_dimensions)
	{
	}

	template<typename T>
	inline H3FastMap<T>::iterator::iterator(H3FastMap* map, UINT x, UINT y, UINT z) :
		m_current(map->at(x, y, z)),
		m_dimensions(map->m_dimensions)
	{
	}

	template<typename T>
	inline H3FastMap<T>::iterator::iterator(pointer item, UINT map_size) :
		m_current(item),
		m_dimensions(map_size)
	{
	}

	template<typename T>
	inline typename H3FastMap<T>::reference H3FastMap<T>::iterator::operator*() const
	{
		return *m_current;
	}

	template<typename T>
	inline typename H3FastMap<T>::pointer H3FastMap<T>::iterator::operator&() const
	{
		return m_current;
	}

	template<typename T>
	inline typename H3FastMap<T>::pointer H3FastMap<T>::iterator::operator->() const
	{
		return m_current;
	}
	template<typename T>
	inline typename H3FastMap<T>::iterator H3FastMap<T>::begin()
	{
		return iterator(this, 0, 0, 0);
	}
	template<typename T>
	inline typename H3FastMap<T>::iterator H3FastMap<T>::end()
	{
		return iterator(this, 0, 0, m_levels);
	}
	template<typename T>
	inline typename H3FastMap<T>::iterator H3FastMap<T>::operator()(UINT x, UINT y, UINT z)
	{
		return iterator(this, x, y, z);
	}
	template<typename T>
	inline H3FastMap<T>::H3FastMap(pointer base, UINT map_size, BOOL has_underground) :
		m_base(base),
		m_dimensions(map_size),
		m_levels(has_underground ? 2 : 1)
	{
	}
	template<typename T>
	inline typename H3FastMap<T>::reference H3FastMap<T>::At(UINT x, UINT y, UINT z)
	{
		return *at(x, y, z);
	}
	template<typename T>
	inline H3Point H3FastMap<T>::GetCoordinates(const iterator& it)
	{
		return GetCoordinates(&it);
	}
	template<typename T>
	inline H3Point H3FastMap<T>::GetCoordinates(pointer item)
	{
		H3Point p;
		UINT delta = item - m_base;
		p.x = delta % m_dimensions;
		delta /= m_dimensions;
		p.y = delta % m_dimensions;
		p.z = delta / m_dimensions;
		return p;
	}
	template<typename T>
	inline typename H3FastMap<T>::pointer H3FastMap<T>::at(UINT x, UINT y, UINT z)
	{
		return &m_base[x + m_dimensions * (y + z * m_dimensions)];
	}
}

#endif /* #define _H3BASE_INL_ */