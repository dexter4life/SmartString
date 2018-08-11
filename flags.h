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