#ifndef __NL_EXCEPTION_H__
#define __NL_EXCEPTION_H__

//--------------------------------------------------------------------------------------

#include "Common.h"

#include "Log.h"

////////////////////////////////////////////////////////////////////////////////////////

namespace NL
{	

	class Exception
	{
	public:

		Exception();
		explicit Exception(const String &message);

		virtual ~Exception();

		String GetMessage();

	protected:

		String Message;

	};

};

#endif