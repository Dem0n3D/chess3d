#include "Log.h"

NL::Log* NL::Singleton<NL::Log>::ms_Singleton = 0;

//--------------------------------------------------------------------------------------

NL::Log::Log()
{
	lines.clear();
};

NL::Log::~Log()
{
	lines.clear();
};

void NL::Log::Add(const String &str,const String &clr)
{
	Stringstream line;
	line << "<font color = " << clr << ">" << str << "</font>";

	lines.push_back(line.str());
};

void NL::Log::AddLine(const String &str,const String &clr)
{
	Stringstream line;
	line << "<font color = " << clr << ">" << str << "</font><br>";

	lines.push_back(line.str());
};

void NL::Log::NewLine()
{
	lines.push_back(NL_T("<br>"));
};

void NL::Log::Save(const String &filename)
{
	std::ofstream f(filename.c_str());

	for(std::list<String>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		f << (*it).c_str();
	}

	f.close();
};