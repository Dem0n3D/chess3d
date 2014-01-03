#ifndef __NL_FREETYPE_H__
#define __NL_FREETYPE_H__

//--------------------------------------------------------------------------------------

//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

//--------------------------------------------------------------------------------------

//OpenGL Headers 
#ifdef WIN32
	#include <windows.h>		//(the GL headers need it)
#endif

#include <GL/gl.h>
#include <GL/glu.h>

//--------------------------------------------------------------------------------------

#include "../Common.h"

//--------------------------------------------------------------------------------------

#ifdef _WIN32

	#ifdef _DEBUG
		#pragma comment(lib,"freetype231_D.lib")
	#else
		#pragma comment(lib,"freetype231.lib")
	#endif

		#pragma comment(lib,"opengl32.lib")
		#pragma comment(lib,"glu32.lib")

#endif

//--------------------------------------------------------------------------------------

//MSVC will spit out all sorts of useless warnings if
//you create vectors of strings, this pragma gets rid of them.
#pragma warning(disable: 4786) 

///Wrap everything in a namespace, that we can use common
///function names like "print" without worrying about
///overlapping with anyone else's code.
namespace freetype
{

	//Inside of this namespace, give ourselves the ability
	//to write just "vector" instead of "std::vector"
	using std::vector;

	//Ditto for string.
	using std::string;

	//This holds all of the information related to any
	//freetype font that we want to create.  
	struct font_data
	{
		float h;			///< Holds the height of the font.
		GLuint * textures;	///< Holds the texture id's 
		GLuint list_base;	///< Holds the first display list id

		//The init function will create a font of
		//of the height h from the file fname.
		void init(const char * fname, unsigned int h);

		//Free all the resources assosiated with the font.
		void clean();
	};

	//The flagship function of the library - this thing will print
	//out text at window coordinates x,y, using the font ft_font.
	//The current modelview matrix will also be applied to the text. 
	void print(const font_data &ft_font, float x, float y, const char *fmt, ...) ;

}

#endif