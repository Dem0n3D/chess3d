#ifndef __NL_COMMON_H__
#define __NL_COMMON_H__

//--------------------------------------------------------------------------------------
// ���������� ������������ �����
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// STL
//--------------------------------------------------------------------------------------

#include <map>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <functional>

//--------------------------------------------------------------------------------------
// ���������
//--------------------------------------------------------------------------------------

#include <stdio.h>

namespace NL
{

#pragma warning ( disable : 4996 )

	//--------------------------------------------------------------------------------------
	// ���������� ������
	//--------------------------------------------------------------------------------------

	#ifdef _UNICODE
		typedef wchar_t NCHAR;
		typedef std::wstring String;
		typedef std::wstringstream Stringstream;
		#define NL_T(x) L##x
	#else
		typedef char NCHAR;
		typedef std::string String;
		typedef std::stringstream Stringstream;		
		#define NL_T(x) x
	#endif

	inline String IntToStr(int i)
	{
		char buff[100];
		itoa(i,buff,10);
		return String(buff);
	};

	inline int StrToInt(const String &str)
	{
		return atoi(str.c_str());
	};

	inline String copy(const String &str,size_t count,size_t offset)
	{
		String out="";
		for(size_t i = offset; (i < str.length()) && (i-offset < count); i++)
			out += str[i];
		return out;
	};

	//--------------------------------------------------------------------------------------
	// ��������������� ����
	//--------------------------------------------------------------------------------------

	#ifndef DWORD
		typedef unsigned long DWORD;
	#endif

	#ifndef COLOR
		typedef unsigned long COLOR;
	#endif

	#ifndef WORD
		typedef unsigned short WORD;
	#endif

	#ifndef BYTE
			typedef unsigned char BYTE;
	#endif

	//--------------------------------------------------------------------------------------
	// ��������������� �������
	//--------------------------------------------------------------------------------------

	#define SET_ACCESSOR( x, y )       inline void Set_##y( x t )  { y = t; };
	#define GET_ACCESSOR( x, y )       inline x Get_##y() { return y; };
	#define GET_SET_ACCESSOR( x, y )   SET_ACCESSOR( x, y ) GET_ACCESSOR( x, y )

	#ifndef __max
		#define __max(a,b) (a>b)?a:b
	#endif
	#ifndef __min
		#define __min(a,b) (a<b)?a:b
	#endif

	//--------------------------------------------------------------------------------------
	// ��������������� �������
	//--------------------------------------------------------------------------------------

	template<typename T> inline void SWAP(T &a,T &b)
	{
		T c = a;
		a = b;
		b = c;
	}

};

#endif