#ifndef __NL_LOG_H__
#define __NL_LOG_H__

#include "Common.h"

#include "Singleton.h"

//ÀÓ„

namespace NL
{	

	class Log : public Singleton<Log>
	{
	public:

		Log();
		~Log();

		void Add(const String &str,const String &clr = NL_T("black"));
		void AddLine(const String &str,const String &clr = NL_T("black"));

		void NewLine();
		
		void Save(const String &filename);

	private:

		std::list<String> lines;

	};

	#define ADD_LOG(a,b) { if(b){ NL::Log::getSingleton().Add(a);  NL::Log::getSingleton().AddLine(" Success","green"); }else{  NL::Log::getSingleton().Add(a);  NL::Log::getSingleton().AddLine("Fail","red"); } }

};

#endif