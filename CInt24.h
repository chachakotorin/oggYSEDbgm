#pragma once

/**
* Int24 definition
*/
const int INT24_MAX = 8388607;

class Int24
{
private:
	unsigned char m_Internal[3];
public:
	inline void setval(int input) {
		m_Internal[0] = ((unsigned char*)&input)[0];
		m_Internal[1] = ((unsigned char*)&input)[1];
		m_Internal[2] = ((unsigned char*)&input)[2];
	}
	inline int getval() const {
		if (m_Internal[2] & 0x80) // Is this a negative?  Then we need to siingn extend.
		{
			return (0xff << 24) | (m_Internal[2] << 16) | (m_Internal[1] << 8) | (m_Internal[0] << 0);
		}
		else
		{
			return (m_Internal[2] << 16) | (m_Internal[1] << 8) | (m_Internal[0] << 0);
		}
	}
	inline void copy(const Int24& input) {
		m_Internal[0] = input.m_Internal[0];
		m_Internal[1] = input.m_Internal[1];
		m_Internal[2] = input.m_Internal[2];
	}

public:
	Int24() {}
	Int24(const int val) { setval(val); }
	Int24(const Int24& val) { copy(val); }
	operator int() const { return getval(); }
	operator long() const { return getval(); }
	operator double() const { return getval(); }
	Int24& operator =(const Int24& input) { copy(input); return *this; }
	Int24& operator =(const int input) { setval(input); return *this; }

	/***********************************************/

	operator bool() const { return getval() != 0; }
	bool operator !() const { return !(getval()); }
	Int24 operator -() { return Int24(-getval()); }

	bool operator ==(const Int24& val) const { return getval() == val.getval(); }
	bool operator !=(const Int24& val) const { return getval() != val.getval(); }
	bool operator >=(const Int24& val) const { return getval() >= val.getval(); }
	bool operator <=(const Int24& val) const { return getval() <= val.getval(); }
	bool operator > (const Int24& val) const { return getval() >  val.getval(); }
	bool operator < (const Int24& val) const { return getval() <  val.getval(); }

	Int24 operator +(const Int24& val) const { return Int24(getval() + val.getval()); }
	Int24 operator -(const Int24& val) const { return Int24(getval() - val.getval()); }
	Int24 operator *(const Int24& val) const { return Int24(getval() * val.getval()); }
	Int24 operator /(const Int24& val) const { return Int24(getval() / val.getval()); }
	Int24 operator %(const Int24& val) const { return Int24(getval() % val.getval()); }
	Int24 operator >>(const Int24& val) const { return Int24(getval() >> val.getval()); }
	Int24 operator <<(const Int24& val) const { return Int24(getval() << val.getval()); }

	Int24& operator +=(const Int24& val) { setval(getval() + val.getval()); return *this; }
	Int24& operator -=(const Int24& val) { setval(getval() - val.getval()); return *this; }
	Int24& operator *=(const Int24& val) { setval(getval() * val.getval()); return *this; }
	Int24& operator /=(const Int24& val) { setval(getval() / val.getval()); return *this; }
	Int24& operator %=(const Int24& val) { setval(getval() % val.getval()); return *this; }
	Int24& operator <<=(const Int24& val) { setval(getval() << val.getval()); return *this; }
	Int24& operator >>=(const Int24& val) { setval(getval() >> val.getval()); return *this; }


};

#define decl_external_Int24_cmp_operator(NUM) \
bool operator ==( const Int24& a, NUM b) { return a.getval() == b; } \
bool operator !=( const Int24& a, NUM b) { return a.getval() != b; } \
bool operator >=( const Int24& a, NUM b) { return a.getval() >= b; } \
bool operator <=( const Int24& a, NUM b) { return a.getval() <= b; } \
bool operator > ( const Int24& a, NUM b) { return a.getval() >  b; } \
bool operator < ( const Int24& a, NUM b) { return a.getval() <  b; } \
bool operator ==( NUM b, const Int24& a) { return b == a.getval(); } \
bool operator !=( NUM b, const Int24& a) { return b != a.getval(); } \
bool operator >=( NUM b, const Int24& a) { return b >= a.getval(); } \
bool operator <=( NUM b, const Int24& a) { return b <= a.getval(); } \
bool operator > ( NUM b, const Int24& a) { return b >  a.getval(); } \
bool operator < ( NUM b, const Int24& a) { return b <  a.getval(); }

#define decl_external_Int24_arith_operator(NUM) \
NUM operator +( const Int24& val, NUM b ) {return val.getval() + b;} \
NUM operator -( const Int24& val, NUM b ) {return val.getval() - b;} \
NUM operator *( const Int24& val, NUM b ) {return val.getval() * b;} \
NUM operator /( const Int24& val, NUM b ) {return val.getval() / b;} \
NUM operator +( NUM b, const Int24& val ) {return b + val.getval();} \
NUM operator -( NUM b, const Int24& val ) {return b - val.getval();} \
NUM operator *( NUM b, const Int24& val ) {return b * val.getval();} \
NUM operator /( NUM b, const Int24& val ) {return b / val.getval();}

#define decl_external_Int24_intarith_operator(NUM) \
NUM operator %( const Int24& val, NUM b ) {return val.getval() % b;} \
Int24 operator >>( const Int24& val, NUM b ) {return Int24( val.getval() >> b );} \
Int24 operator <<( const Int24& val, NUM b ) {return Int24( val.getval() << b );} \
NUM operator %( NUM b, const Int24& val ) {return b % val.getval();} \
NUM operator >>( NUM b, const Int24& val ) {return b >> val.getval();} \
NUM operator <<( NUM b, const Int24& val ) {return b << val.getval();}

decl_external_Int24_cmp_operator(int);
decl_external_Int24_cmp_operator(long);
decl_external_Int24_cmp_operator(double);
decl_external_Int24_arith_operator(int);
decl_external_Int24_arith_operator(long);
decl_external_Int24_arith_operator(double);
decl_external_Int24_intarith_operator(int);
decl_external_Int24_intarith_operator(long);
