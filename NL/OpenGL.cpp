#include "Renderer/OpenGL.h"

//--------------------------------------------------------------------------------------

NL::OpenGL* NL::Singleton<NL::OpenGL>::ms_Singleton = 0;

//--------------------------------------------------------------------------------------

using namespace NL::Math;

////////////////////////////////////////////////////////////////////////////////////////

NL::OpenGL::OpenGL()
{
	Matrix4x4 m;
	mst.push(m.Identity());
};

NL::OpenGL::~OpenGL()
{

};
bool NL::OpenGL::Initialize()
{
	glClearColor( 1, 1, 1, 1 );
	glEnable( GL_DEPTH_TEST );
	/*glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);*/

	//--------------------------------------------------------------------------------------
	// ������������� ���������� ����������

	//Log::getSingleton().Add("Initializing textures...");

	ilInit(); // ������������� �������� ����������
	iluInit(); // ������������� ���������� ������

	int err = ilGetError();
	ADD_LOG("Initializing textures...",err == IL_NO_ERROR);

	if(err != IL_NO_ERROR)
	{
		const char* strError = iluErrorString(err);
		// ������ ��������� �� ������
		Log::getSingleton().AddLine(strError,"red");
	}

	//--------------------------------------------------------------------------------------

	initExtensions();

	return true;
};

/*void NL::OpenGL::DrawText(const String &family,unsigned int size,const String &text)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	static bool b = false;
	static freetype::font_data our_font;
	if(!b)
		our_font.init((family+".TTF").c_str(),size);		//Build the freetype font
	b = true;
	freetype::print(our_font,0,550,text.c_str());
};*/

//--------------------------------------------------------------------------------------
// �������� ��� ��������� � ������

void NL::OpenGL::LoadMatrix(unsigned int mode,const Math::Matrix4x4 &mat)
{
	switch(mode)
	{
	case M_VIEW:
		ViewMatrix = mat;
		break;
	case M_PROJECTION:
		ProjectionMatrix = mat;
		break;		
	case M_WORLD:
		{
			mst.pop();
			mst.push(mat);
			break;
		}

		// ������ ��������!
	}
};

void NL::OpenGL::LoadIdentityMatrix(unsigned int mode)
{
	Matrix4x4 mat;
	LoadMatrix(mode,mat.Identity());
};

void NL::OpenGL::MultMatrix(unsigned int mode,const Math::Matrix4x4 &mat)
{
	switch(mode)
	{
	case M_VIEW:
		ViewMatrix *= mat;
		break;
	case M_PROJECTION:
		ProjectionMatrix *= mat;
		break;		
	case M_WORLD:
		{
			mst.Mul(mat);
			break;
		}

		// ������ ��������!
	}
};

void NL::OpenGL::PushMatrix()
{
	Matrix4x4 m;
	mst.push(m.Identity());
};

void NL::OpenGL::PopMatrix()
{
	mst.pop();
};

NL::Math::Matrix4x4 NL::OpenGL::GetMatrix(unsigned int mode)
{
	switch(mode)
	{
	case M_VIEW:
		return ViewMatrix;
	case M_PROJECTION:
		return ProjectionMatrix;
	case M_WORLD:
		return mst.top();

		// ������ ��������!

	default:
		{
			Matrix4x4 tmpm;
			return tmpm.Nil();
		}
	}
};

//--------------------------------------------------------------------------------------
// ��������

int  NL::OpenGL::LoadTexture(const String &filename)
{
	ilLoad(IL_TYPE_UNKNOWN,(const ILstring)filename.c_str());	
	//��������� ���� ������
	int err = ilGetError();
	//���� ��� �� ����� ���� ��
	if (err != IL_NO_ERROR)
	{
		return -1;	
	}
	//������ �����������
	int width = ilGetInteger(IL_IMAGE_WIDTH); 
	//����� �����������
	int height = ilGetInteger(IL_IMAGE_HEIGHT); 
	//����� ���� �� �������	
	int bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); 	
	//������ ������
	int size = width * height * bpp;
	//������ ��� ������
	unsigned char* data = new unsigned char[size];
	//��������� ��������� ������
	unsigned char *copyData = ilGetData();
	//����������� ��������� ������
	memcpy(data, copyData, size);
	//��� �������� ������
	unsigned int type;
	//�������������� ��� ��� OpenGL
	switch (bpp) {
	case 1:	
		type  = GL_RGB8;
		break;
	case 3:
		type = 	GL_RGB;
		break;
	case 4:
		type = GL_RGBA;
		break;
	}
	unsigned int IndexTexture = -1;
	glGenTextures(1, &IndexTexture);  
	glBindTexture(GL_TEXTURE_2D, IndexTexture); 	
	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, width, height, type, 
		GL_UNSIGNED_BYTE, data);		
	//�������� ��������� �������
	if (data) {
		delete [] data;
		data = NULL;
	}

	return IndexTexture;
};

void NL::OpenGL::SetTexture(int index)
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, index );
};

//--------------------------------------------------------------------------------------
// ����������

bool NL::OpenGL::IsExtensionSupported(const String &extname)
{
	const char * extensions = (const char *)glGetString(GL_EXTENSIONS);
	const char * start      = extensions;
	const char * ptr		= NULL;
	
	while(ptr = strstr(start,extname.c_str()))
	{
		const char *end = ptr + strlen(extname.c_str());

		if (isspace(*end) || *end == '\0')
			return true;

		start = end;
	}

	return false;
};

void NL::OpenGL::Release()
{

};

void NL::OpenGL::ApplyTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((float *)&(mst.top() * ViewMatrix));

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((float *)&ProjectionMatrix);
};