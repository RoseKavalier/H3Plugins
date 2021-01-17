//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BASE_HPP_
#define _H3BASE_HPP_

#include "../H3_Core.hpp"
#include "../H3_Config.hpp"
#include "../H3_Allocator.hpp"

namespace h3
{
	/**
	 * @brief Null string ""
	 *
	 */
	LPCSTR const h3_NullString = LPCSTR(0x63A608);
	/**
	 * @brief 512 bytes of char buffer to be used for printing text
	 *
	 */
	PCHAR  const h3_TextBuffer = PCHAR(0x697428);
	/**
	 * @brief path to the main directory of the game
	 *
	 */
	LPCSTR const h3_GamePath   = LPCSTR(0x698614);
	/**
	 * @brief a text buffer used to save the game
	 *
	 */
	PCHAR  const h3_SaveName   = PCHAR(0x69FC88);

	/**
	 * @brief detects H3 exe version at runtime
	 *
	 */
	class H3Version
	{
	public:
		_H3API_ENUM_ GameVersion : INT32
		{
			UNKNOWN         = -1,
			ROE             = 0,
			SOD             = 1,
			SOD_POLISH_GOLD = 2,
			HOTA            = 3,
			ERA             = 4,
			WOG             = 5,
		};
		/**
		 * @brief the constructor is required to detect the exe type
		 */
		_H3API_ H3Version();
		/**
		 * @brief returns the detected exe version
		 *
		 * @return GameVersion a value matching the current exe
		 */
		_H3API_ GameVersion version() const;
		/**
		 * @brief compares the exe version to Restoration of Erathia
		 *
		 * @return true if the current exe is RoE
		 */
		_H3API_ BOOL roe()  const;
		/**
		 * @brief compares the exe version to Shadow of Death 3.2
		 *
		 * @return true if the current exe is SoD 3.2
		 */
		_H3API_ BOOL sod()  const;
		/**
		 * @brief compares the exe version to Horn of the Abyss
		 *
		 * @return true if the current exe is HotA
		 */
		_H3API_ BOOL hota() const;
		/**
		 * @brief compares the exe version to ERA II
		 *
		 * @return true if the current exe is ERA
		 */
		_H3API_ BOOL era()  const;
		/**
		 * @brief compares the exe version to Wake of Gods
		 *
		 * @return true if the current exe is WOG
		 */
		_H3API_ BOOL wog()  const;
	private:
		GameVersion m_version;
	};

	/**
	 * @brief memcpy using H3 assets
	 *
	 * @param dest the destination of the memory block to copy
	 * @param src the source of the memory block that is being copied
	 * @param len how many bytes should be copied
	 * @return _H3API_
	 */
	_H3API_ VOID F_memcpy(PVOID dest, PVOID src, const UINT len);
	/**
	 * @brief strcmpi using H3 assets, compares 2 c-strings case insensitive
	 *
	 * @param string1 the first string to compare
	 * @param string2 the second string to compare
	 * @return INT which string is smaller or 0 on equality
	 */
	_H3API_ INT F_strcmpi(LPCSTR string1, LPCSTR string2);
	/**
	 * @brief memset using H3 assets
	 *
	 * @param dest the destination block
	 * @param value the uniform value to set at the specified block
	 * @param len the number of bytes to set
	 */
	_H3API_ PVOID F_memset(PVOID dest, const UINT value, const UINT len);
	/**
	 * @brief vsprintf using h3 assets
	 * you need to handle va_list yourself to use this!
	 * otherwise use F_sprintf which will do both
	 * @param buffer a char[] buffer to write the formatted string
	 * @param format how the string should be formatted
	 * @param args arguments required to format the string as specified
	 * @return INT the number of bytes written
	 */
	_H3API_ INT F_vsprintf(PCHAR buffer, LPCSTR format, va_list args);
	/**
	 * @brief sprintf using H3 assets and h3_textBuffer
	 *
	 * @param format how the string should be formatted
	 * @param ... arguments required to format the string as specified
	 * @return INT the number of bytes written
	 */
	_H3API_ INT F_sprintf(LPCSTR format, ...);
	// * sprintf using h3 assets and custom buffer
	/**
	 * @brief sprintf using H3 assets and a custom buffer
	 *
	 * @param buffer a char[] buffer to write the formatted string
	 * @param format how the string should be formatted
	 * @param ... arguments required to format the string as specified
	 * @return INT the number of bytes written
	 */
	_H3API_ INT F_sprintfbuffer(PCHAR buffer, LPCSTR format, ...);

	namespace H3Numbers
	{
		/**
		 * @brief add thousands commas to numbers, e.g. 123,456 instead of 123456
		 *
		 * @param num the number to format
		 * @param out a char[] buffer to receive the formatted number
		 * @return the number of bytes written
		 */
		_H3API_ INT AddCommas(INT num, CHAR *out);
		/**
		 * @brief show a number in short scale format with specified number of decimals
		 * e.g. 123,456,789 in short scale can be 123.5M for 1 decimal
		 * @param num the number to format
		 * @param out a char[] buffer to receive the formatted number
		 * @param decimals the number of decimals to use after the period
		 * @return the number of bytes written
		 */
		_H3API_ INT MakeReadable(INT num, CHAR *out, INT decimals = 1);
	}

	namespace H3Random
	{
		/**
		 * @brief Set the Random Seed object
		 *
		 * @param seed the default seed uses H3's current seed
		 */
		_H3API_ VOID  SetRandomSeed(UINT seed = STDCALL_0(UINT, DwordAt(0x63A354)));
		/**
		 * @brief generates a random number
		 *
		 * @param high the upper margin of the number to be generated
		 * @return a random number between 0 and \p high
		 */
		_H3API_ INT32 Random(INT32 high);
		/**
		 * @brief generates a random number in the specified interval
		 *
		 * @param low the lower boundary
		 * @param high the upper boundary
		 * @return a random number between \p low and \p high
		 */
		_H3API_ INT32 RandBetween(INT32 low, INT32 high);
	}

	namespace H3Error
	{
		/**
		 * @brief displays MessageBox with custom message and title
		 *
		 * @param message the message to be shown
		 * @param title title of the MessageBox
		 */
		_H3API_ VOID ShowError(LPCSTR message, LPCSTR title = "H3Error!");
		/**
		 * @brief displays MessageBox with custom message, title and OK / Cancel choice
		 *
		 * @param message the message to be shown
		 * @param title title of the MessageBox
		 * @return true if the user clicked OK
		 */
		_H3API_ BOOL ShowErrorChoice(LPCSTR message, LPCSTR title = "H3Error!");
		/**
		 * @brief displays MessageBox with custom UNICODE message and title
		 *
		 * @param message the message to be shown
		 * @param title title of the MessageBox
		 */
		_H3API_ VOID ShowErrorW(LPCWSTR message, LPCWSTR title = L"H3Error!");
		/**
		 * @brief displays MessageBox with custom UNICODE message, title and OK / Cancel choice
		 *
		 * @param message the message to be shown
		 * @param title title of the MessageBox
		 * @return true if the user clicked OK
		 */
		_H3API_ BOOL ShowErrorChoiceW(LPCWSTR message, LPCWSTR title = L"H3Error!");
	}

#pragma pack(push, 4)
	/**
	 * @brief DWORD used as a bitfield
	 * can be used as an array of bitfields (no bound checking)
	 * for a safer and more developped version with iterators, use H3Bitset
	 */
	struct H3Bitfield
	{
		/**
		 * @brief similar to bitset::reference
		 * holds a pointer to Bitfield start and allows specific operations on indexed bits
		 */
		struct reference
		{
		protected:
			H3Bitfield* m_bitfield;
			UINT32      m_position;
		public:
			_H3API_ reference(H3Bitfield* bitfield);
			_H3API_ reference(H3Bitfield* bitfield, UINT position);
			/**
			 * @brief pre-increment
			 *
			 * @return itself, the next reference
			 */
			_H3API_ reference& operator++();
			/**
			 * @brief post-increment
			 *
			 * @return a copy of the current reference
			 */
			_H3API_ reference operator++(int);
			/**
			 * @brief flips the current bit
			 *
			 * @return itself
			 */
			_H3API_ reference& operator~();
			/**
			 * @brief allows if (reference) condition to be used
			 *
			 * @return true if the current bit is set, false otherwise
			 */
			_H3API_ operator BOOL();
			/**
			 * @brief allows if (!reference) condition to be used
			 *
			 * @return true if the current bit is not set, false otherwise
			 */
			_H3API_ BOOL operator!();
			/**
			 * @brief set the state of the current bit
			 *
			 * @param state true (on) or false (off)
			 */
			_H3API_ VOID operator=(BOOL state);
			/**
			 * @brief sets the current bit to true (on)
			 */
			_H3API_ VOID Set();
			/**
			 * @brief sets the current bit to false (off)
			 */
			_H3API_ VOID Reset();
			/**
			 * @brief Flips the current bit
			 */
			_H3API_ VOID Flip();
		};

	protected:
		UINT m_bf;
	public:
		/**
		 * @brief returns whether bit at position is set or not
		 *
		 * @param position can exceed the scope of bitfield, meaning greater than 32 bits
		 * @return true if the specified bit is set
		 */
		_H3API_ BOOL GetState(UINT32 position) const;
		/**
		 * @brief Set the state of the specified bit
		 *
		 * @param position can exceed the scope of bitfield, meaning greater than 32 bits
		 * @param state true (on) or false (off)
		 */
		_H3API_ VOID SetState(UINT32 position, BOOL state);
		// * Sets bitfield to specified value
		/**
		 * @brief Sets the underlying DWORD to the specified value
		 *
		 * @param value the new bitfield state
		 */
		_H3API_ VOID Set(UINT32 value);
		/**
		 * @brief Get underlying DWORD value
		 *
		 * @return the current state of the bitfield
		 */
		_H3API_ UINT Get() const;
		/**
		 * @brief flips bit at position
		 *
		 * @param position can exceed the scope of bitfield, meaning greater than 32 bits
		 * @return _H3API_
		 */
		_H3API_ VOID Flip(UINT32 position);
		// * get reference at position
		/**
		 * @brief get reference at position
		 * using reference allows expressions that would otherwise be impossible such as:
		 * Bitfield[33] = true;
		 * @param position can exceed the scope of bitfield, meaning greater than 32 bits
		 * @return a reference to the specified position
		 */
		_H3API_ reference operator[](UINT32 position);
		/**
		 * @brief state of bit at position
		 *
		 * @param position can exceed the scope of bitfield, meaning greater than 32 bits
		 * @return true if the bit is set/on, false otherwise
		 */
		_H3API_ BOOL operator()(UINT position);
		/**
		 * @brief the end mask of unusable bits for a bitfield with specified number of bits
		 *
		 * @param number_bits the total number of bits in the bitset represented
		 * @return the value of the end mask, that is all bits that are not part of the last 32 bits
		 */
		_H3API_ static UINT Mask(UINT number_bits);
	};

	/**
	 * @brief 8x6 mask for properties and drawing of adventure map objects
	 * (0,0) is bottom right corner and corresponds to bit 0
	 * bit increments go left to right and then bottom to top, e.g.
	 * bit 0 (0, 0)
	 * bit 1 (1, 0)
	 * bit 8 (7, 0)
	 * bit 9 (0, 1)
	 */
	struct H3ObjectMask
	{
		union
		{
			H3Bitfield m_bits[2];
			UINT64     m_bitsPacked;
		};

		/**
		 * @brief an incrementable structure over the object mask with additional functionality
		 *
		 */
		class iterator
		{
		private:
			H3ObjectMask* m_mask;
			UINT32        m_position;
		public:
			_H3API_ iterator(const iterator& it);
			_H3API_ iterator(H3ObjectMask* mask);
			_H3API_ iterator(H3ObjectMask* mask, UINT32 index);
			/**
			 * @brief pre-increment
			 *
			 * @return itself
			 */
			_H3API_ iterator& operator++();
			/**
			 * @brief post-increment
			 *
			 * @return a copy of itself before increment
			 */
			_H3API_ iterator operator++(int);
			/**
			 * @brief flips current bit from on to off and vice-versa
			 *
			 * @return itself
			 */
			_H3API_ iterator& operator~();
			/**
			 * @brief allows if (iterator) condition to be used
			 *
			 * @return BOOL true if the current bit is set, otherwise false
			 */
			_H3API_ operator BOOL() const;
			/**
			 * @brief allows if (!iterator) condition to be used
			 *
			 * @return BOOL true if the current bit is not set, otherwise false
			 */
			_H3API_ BOOL operator!() const;
			/**
			 * @brief set the state of the current bit
			 *
			 * @param state TRUE/on or FALSE/off
			 */
			_H3API_ VOID operator=(BOOL state);
			/**
			 * @brief Get the state of the current bit
			 *
			 * @return BOOL true if the bit is set, false otherwise
			 */
			_H3API_ BOOL GetState() const;
			/**
			 * @brief set the state of the current bit
			 *
			 * @param state TRUE/on or FALSE/off
			 */
			_H3API_ VOID SetState(BOOL state);
			/**
			 * @brief set the current bit as ON / true
			 */
			_H3API_ VOID Set();
			/**
			 * @brief set the current bit as OFF / false
			 */
			_H3API_ VOID Reset();
			/**
			 * @brief flips current bit from on to off and vice-versa
			 */
			_H3API_ VOID Flip();
			/**
			 * @brief equality comparison between two iterators
			 *
			 * @param it another iterator
			 * @return BOOL whether both iterators are at the same position
			 */
			_H3API_ BOOL operator==(const iterator& it);
			/**
			 * @brief inequality comparison between two iterators
			 *
			 * @param it another iterator
			 * @return BOOL whether both iterators are not at the same position
			 */
			_H3API_ BOOL operator!=(const iterator& it);
		};
		/**
		 * @brief copies another object mask state
		 *
		 * @param other a second object mask
		 */
		_H3API_ VOID operator=(const H3ObjectMask& other);
		/**
		 * @brief copies 64 bits of data to current state
		 * note that only 48 bits are used, the remaining 16 have no impact whatsoever
		 * @param value the new state of the mask to use
		 */
		_H3API_ VOID operator=(UINT64 value);
		/**
		 * @brief get access to the internal bitfield
		 * Used for Lod-type H3Msk assignment
		 * @param index 0..1
		 * @return H3Bitfield the first or second bitfield of the object
		 */
		_H3API_ H3Bitfield& operator[](UINT index);
		/**
		 * @brief get access to the internal bitfield
		 *
		 * @param index 0..1
		 * @return H3Bitfield the first or second bitfield of the object
		 */
		_H3API_ const H3Bitfield& operator[](UINT index) const;
		/**
		 * @brief an incrementable iterator matching H3 access order start
		 *
		 * @return iterator for bottom right corner
		 */
		_H3API_ iterator begin();
		/**
		 * @brief an incrementable iterator matching H3 access order end
		 *
		 * @return iterator for 6th row (counting from 0)
		 */
		_H3API_ iterator end();
		/**
		 * @brief an iterator to the specified position
		 * allows some extra access e.g.
		 * mask(0) = true;
		 * @param index 0..47 starting from bottom right
		 * @return iterator to specified position
		 */
		_H3API_ iterator operator()(UINT8 index);
		/**
		 * @brief an iterator to the specified coordinates
		 * allows some extra access e.g.
		 * mask(0, 0) = true;
		 * @param column 0..7 counting from right to left
		 * @param row 0..5 counting from bottom to top
		 * @return iterator to specified coordinates
		 */
		_H3API_ iterator operator()(UINT8 column, UINT8 row);
	};

	/**
	 * @brief represents a x-y-z point on the map
	 */
	struct H3Point
	{
		UINT32 x;
		UINT32 y;
		UINT32 z;

		_H3API_ H3Point();
		_H3API_ H3Point(UINT32 x, UINT32 y, UINT32 z);
		_H3API_ H3Point(const H3Point& pt);
		_H3API_ H3Point& operator=(const H3Point& pt);
		_H3API_ BOOL     operator==(const H3Point& pt);
		_H3API_ BOOL     operator!=(const H3Point& pt);
	};

	/**
	 * @brief represents T* array as [x][y][z] map since they are created as T* map = new T[number_cells];
	 * maps are always square in h3 so only 1 dimension is used for x & y
	 * @tparam T type of the map object
	 */
	template<typename T>
	class H3Map
	{
	public:
		typedef T* pointer;
		typedef T& reference;

		/**
		 * @brief incrementable iterator to to go over the map's span
		 */
		class iterator
		{
		public:
			/**
			 * @brief Construct a new iterator object
			 *
			 * @param it an existing iterator
			 */
			iterator(const iterator& it);
			/**
			 * @brief Construct a new iterator object
			 *
			 * @param map base array of the map
			 * @param x 0..mapsize-1
			 * @param y 0..mapsize-1
			 * @param z 0..1
			 */
			iterator(H3Map* map, UINT x, UINT y, UINT z);
			/**
			 * @brief Construct a new iterator object without known coordinates
			 *
			 * @param map base array of the map
			 * @param item an object from the current map
			 */
			iterator(H3Map* map, pointer item);
			/**
			 * @brief equality comparison
			 *
			 * @param it another iterator
			 * @return BOOL whether both iterators are equal
			 */
			BOOL      operator==(const iterator& it) const;
			/**
			 * @brief inequality comparison
			 *
			 * @param it another iterator
			 * @return BOOL whether both iterators are different
			 */
			BOOL      operator!=(const iterator& it) const;
			/**
			 * @brief pre-increment
			 *
			 * @return itself
			 */
			iterator& operator++();
			/**
			 * @brief post-increment
			 *
			 * @return copy of itself before increment
			 */
			iterator  operator++(int);
			/**
			 * @brief direct access to T contents and methods
			 */
			pointer   operator->() const;
			/**
			 * @brief get address of iterator state
			 *
			 * @return pointer address of current map cell
			 */
			pointer   operator&() const;
			/**
			 * @brief dereference iterator state
			 *
			 * @return reference to current map cell
			 */
			reference operator*() const;
			/**
			 * @brief allows inspection of map cells at an offset from the current one
			 *
			 * @param dx horizontal difference
			 * @param dy vertical difference
			 * @return reference to the map cell at specified offset
			 */
			reference operator()(INT dx, INT dy) const;
			/**
			 * @brief computes the current map cell's horizontal position
			 *
			 * @return UINT 0..mapsize-1
			 */
			UINT      GetX() const;
			/**
			 * @brief computes the current map cell's vertical position
			 *
			 * @return UINT 0..mapsize-1
			 */
			UINT      GetY() const;
			/**
			 * @brief computes the current map cell's level
			 *
			 * @return UINT 0..1
			 */
			UINT      GetZ() const;
			/**
			 * @brief computes the current map cell's position
			 *
			 * @return H3Point (x,y,z)
			 */
			H3Point   Get() const;
		private:
			pointer m_current;
			UINT    m_x;
			UINT    m_y;
			UINT    m_z;
			H3Map*  m_map;
		};
		/**
		 * @brief Construct a new H3Map object
		 *
		 * @param base the start of the map array
		 * @param map_size the unique dimension size since maps are square
		 * @param has_underground whether an underground level is present
		 */
		H3Map(pointer base, UINT map_size, BOOL has_underground);
		/**
		 * @brief the first map cell of the array
		 *
		 * @return iterator (0, 0, 0)
		 */
		iterator begin();
		/**
		 * @brief 1 beyond the last cell of the array
		 *
		 * @return iterator (0, 0, 1 or 2) depending on underground
		 */
		iterator end();
		/**
		 * @brief obtain an iterator for the specified position
		 *
		 * @param x 0..mapsize-1
		 * @param y 0..mapsize-1
		 * @param z 0..1
		 * @return iterator the specified position
		 */
		iterator operator()(UINT x, UINT y, UINT z);
		/**
		 * @brief get a reference to the map cell at specified position
		 *
		 * @param x 0..mapsize-1
		 * @param y 0..mapsize-1
		 * @param z 0..1
		 * @return reference the specified position
		 */
		reference At(UINT x, UINT y, UINT z);

	private:
		pointer at(UINT x, UINT y, UINT z);

		pointer m_base;
		UINT    m_dimensions;
		UINT    m_levels;
	};

	/**
	 * @brief same as H3Map except it doesn't keep track of coordinates
	 * you can recover MapIterator's coordinates through H3FastMap::GetCoordinates(FastMapIterator)
	 * @tparam T type of the map object
	 */
	template<typename T>
	class H3FastMap
	{
	public:
		typedef T* pointer;
		typedef T& reference;

		/**
		 * @brief incrementable iterator to to go over the map's span
		 */
		class iterator
		{
		public:
			/**
			 * @brief Construct a new iterator object
			 *
			 * @param it an existing iterator
			 */
			iterator(const iterator& it);
			/**
			 * @brief Construct a new iterator object
			 *
			 * @param map base array of the map
			 * @param x 0..mapsize-1
			 * @param y 0..mapsize-1
			 * @param z 0..1
			 */
			iterator(H3FastMap* map, UINT x, UINT y, UINT z);
			/**
			 * @brief Construct a new iterator object without known coordinates
			 *
			 * @param map base array of the map
			 * @param item an object from the current map
			 */
			iterator(pointer item, UINT map_size);
			/**
			 * @brief equality comparison
			 *
			 * @param it another iterator
			 * @return BOOL whether both iterators are equal
			 */
			BOOL      operator==(const iterator& it) const;
			/**
			 * @brief inequality comparison
			 *
			 * @param it another iterator
			 * @return BOOL whether both iterators are different
			 */
			BOOL      operator!=(const iterator& it) const;
			/**
			 * @brief pre-increment
			 *
			 * @return itself
			 */
			iterator& operator++();
			/**
			 * @brief post-increment
			 *
			 * @return copy of itself before increment
			 */
			iterator  operator++(int);
			/**
			 * @brief allows inspection of map cells at an offset from the current one
			 *
			 * @param dx horizontal difference
			 * @param dy vertical difference
			 * @return reference to the map cell at specified offset
			 */
			reference operator()(INT dx, INT dy) const;
			/**
			 * @brief dereference iterator state
			 *
			 * @return reference to current map cell
			 */
			reference operator*() const;
			/**
			 * @brief get address of iterator state
			 *
			 * @return pointer address of current map cell
			 */
			pointer   operator&() const;
			/**
			 * @brief direct access to T contents and methods
			 */
			pointer   operator->() const;
		private:
			pointer m_current;
			UINT    m_dimensions;
		};
		/**
		 * @brief Construct a new H3FastMap object
		 *
		 * @param base the start of the map array
		 * @param map_size the unique dimension size since maps are square
		 * @param has_underground whether an underground level is present
		 */
		H3FastMap(pointer base, UINT map_size, BOOL has_underground);
		/**
		 * @brief the first map cell of the array
		 *
		 * @return iterator (0, 0, 0)
		 */
		iterator  begin();
		/**
		 * @brief 1 beyond the last cell of the array
		 *
		 * @return iterator (0, 0, 1 or 2) depending on underground
		 */
		iterator  end();
		/**
		 * @brief obtain an iterator for the specified position
		 *
		 * @param x 0..mapsize-1
		 * @param y 0..mapsize-1
		 * @param z 0..1
		 * @return iterator the specified position
		 */
		iterator  operator()(UINT x, UINT y, UINT z);
		/**
		 * @brief get a reference to the map cell at specified position
		 *
		 * @param x 0..mapsize-1
		 * @param y 0..mapsize-1
		 * @param z 0..1
		 * @return reference the specified position
		 */
		reference At(UINT x, UINT y, UINT z);
		/**
		 * @brief Calculate coordinates from an iterator
		 *
		 * @param it an iterator of the current map
		 * @return H3Point (x, y, z) position of the iterator
		 */
		H3Point   GetCoordinates(const iterator& it);
		/**
		 * @brief Get coordinates from a map cell
		 *
		 * @param item a cell from the current map
		 * @return H3Point (x, y, z) position of the iterator
		 */
		H3Point   GetCoordinates(pointer item);
	private:
		pointer at(UINT x, UINT y, UINT z);

		pointer m_base;
		UINT    m_dimensions;
		UINT    m_levels;
	};
#pragma pack(pop)

	typedef H3Map<UINT16> H3Map_UINT16;
	typedef H3FastMap<UINT16> H3FastMap_UINT16;
} /* namespace h3 */

namespace h3
{
	// * these are internal to H3API to avoid conflicts
	namespace H3Internal
	{
		_H3API_ INT   _gameWidth();
		_H3API_ INT   _gameHeight();
		_H3API_ INT8  _gameEdgeHorizontal();
		_H3API_ INT8  _gameEdgeVertical();
		_H3API_ UINT  _mapSize();
		_H3API_ UINT8 _bitMode();
		_H3API_ PCHAR _textBuffer();
	} /* namespace H3Internal */
} /* namespace h3 */

#endif /* #define _H3BASE_HPP_ */