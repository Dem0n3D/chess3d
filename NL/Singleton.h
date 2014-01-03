#ifndef __NL_SINGLETON_H__
#define __NL_SINGLETON_H__

#include <assert.h>

namespace NL
{

	template<typename T> class Singleton
	{
	public:

		Singleton()
		{
			assert(!ms_Singleton);
			ms_Singleton = (T *)this;
		};

		~Singleton()
		{  
			assert(ms_Singleton); 
			ms_Singleton = 0;  
		};

		static T &getSingleton()
		{  
			assert(ms_Singleton);  
			return *ms_Singleton;
		}

		static T *getSingletonPtr()
		{  
			return ms_Singleton;
		}

	protected:

		static T *ms_Singleton;

	};

};

#endif