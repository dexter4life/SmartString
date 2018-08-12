/*
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

Author: Peter Nwanosike
Email:dexter4life@gmail.com
*/
#pragma once
#include <cstdint>
#include <cstdint>

template<typename Enum>
class CFlags
{
public:
	typedef Enum enum_type;
	typedef uint32_t  Int;

	C_DECL_CONSTEXPR inline CFlags(Enum f) : i(uint32_t(f)) {}
	C_DECL_CONSTEXPR inline CFlags() : i(0) {}
	C_DECL_CONSTEXPR inline CFlags(uint32_t f) : i(f) {}

	C_DECL_CONSTEXPR inline CFlags &operator=(int mask) { i = mask; return *this; }
	C_DECL_CONSTEXPR inline CFlags &operator&=(int mask) { i &= mask; return *this; }
	C_DECL_CONSTEXPR inline CFlags &operator&=(uint32_t mask) { i &= mask; return *this; }
	C_DECL_CONSTEXPR inline CFlags &operator&=(Enum mask) { i &= Int(mask); return *this; }
	C_DECL_CONSTEXPR inline CFlags &operator|=(CFlags f) { i |= f.i; return *this; }
	C_DECL_CONSTEXPR inline CFlags &operator|=(Enum f) { i |= Int(f); return *this; }
	C_DECL_CONSTEXPR inline CFlags &operator^=(CFlags f) { i ^= f.i; return *this; }
	C_DECL_CONSTEXPR inline CFlags &operator^=(Enum f) { i ^= Int(f); return *this; }
	C_DECL_CONSTEXPR inline		   operator Enum() { return Enum(i); }

	C_DECL_CONSTEXPR inline operator Int() const { return i; }

	C_DECL_CONSTEXPR inline CFlags operator|(CFlags f) const { return CFlags(QFlag(i | f.i)); }
	C_DECL_CONSTEXPR inline CFlags operator|(Enum f) const { return CFlags(QFlag(i | Int(f))); }
	C_DECL_CONSTEXPR inline CFlags operator^(CFlags f) const { return CFlags(QFlag(i ^ f.i)); }
	C_DECL_CONSTEXPR inline CFlags operator^(Enum f) const { return CFlags(QFlag(i ^ Int(f))); }
	C_DECL_CONSTEXPR inline CFlags operator&(int mask) const { return CFlags(QFlag(i & mask)); }
	C_DECL_CONSTEXPR inline CFlags operator&(uint32_t mask) const { return CFlags(QFlag(i & mask)); }
	C_DECL_CONSTEXPR inline CFlags operator&(Enum f) const { return CFlags(QFlag(i & Int(f))); }
	C_DECL_CONSTEXPR inline CFlags operator~() const { return CFlags(QFlag(~i)); }
	
	C_DECL_CONSTEXPR inline bool operator!() const { return !i; }

	C_DECL_CONSTEXPR inline bool testFlag(Enum f) const { return (i & Int(f)) == Int(f) && (Int(f) != 0 || i == Int(f)); }
	C_DECL_CONSTEXPR inline CFlags &setFlag(Enum f, bool on = true)
	{
		return on ? (*this |= f) : (*this &= ~f);
	}

private:
	uint32_t i;
};