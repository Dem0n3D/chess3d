#include "OpenGL.h"

using namespace NL::Math;

//--------------------------------------------------------------------------------------

bool NL::cgShader::Load(const String &filename,const String &efuncname,CGGLenum type,OpenGL *render)
{
	CgVertexProfile = cgGLGetLatestProfile(type);
	cgGLSetOptimalOptions(CgVertexProfile);

	CgProgram = cgCreateProgramFromFile(render->Get_CgContext(),CG_SOURCE,filename.c_str(),CgVertexProfile,efuncname.c_str(),NULL);                  

	cgGLLoadProgram(CgProgram);

	render->CheckCgErrors();

	return true;
};

void NL::cgShader::SetMatrix(const String &name,const Math::Matrix4x4 &mat)
{
	CGparameter Matrix = cgGetNamedParameter(CgProgram,name.c_str());

	cgSetMatrixParameterfr(Matrix,(float *)&Math::Transpose(mat));
};

void NL::cgShader::SetMatrixArray(const String &name,const std::vector<Math::Matrix4x4> &mar)
{
	CGparameter mArray = cgGetNamedParameter(CgProgram,name.c_str());

	for(int i = 0; i < (int)mar.size(); i++)
	{
		cgGLSetMatrixParameterfr(cgGetArrayParameter(mArray,i),(float *)&Math::Transpose(mar[i]));
	}
};

void NL::cgShader::SetTexture(const String &name,UINT texture)
{
	CGparameter Texture = cgGetNamedParameter(CgProgram,name.c_str());

	cgGLSetTextureParameter(Texture,texture);
};

//--------------------------------------------------------------------------------------

NL::OpenGL::OpenGL()
{
	Matrix4x4 m;
	mst.push(m.Identity());
};

NL::OpenGL::~OpenGL()
{

};
bool NL::OpenGL::Initialize(Log *log)
{
	this->log = log;

	glClearColor( 0.0f, 0.0f, 100.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	/*glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);*/

	//--------------------------------------------------------------------------------------
	// Инициализация текстурной библиотеки

	//log->Add("Initializing textures...");

	ilInit(); // Инициализация основной библиотеки
	iluInit(); // Инициализация библиотеки утилит

	int err = ilGetError();
	ADD_LOG("Initializing textures...",err == IL_NO_ERROR);

	if(err != IL_NO_ERROR)
	{
		const char* strError = iluErrorString(err);
		// Выдаем сообщение об ошибке
		log->AddLine(strError,"red");
	}

	//--------------------------------------------------------------------------------------
	// Инициализация Cg

	CgContext = cgCreateContext();

	CheckCgErrors();

	//--------------------------------------------------------------------------------------

	return true;
};

void NL::OpenGL::Begin(unsigned int mode)
{
	ApplyTransform();
	glBegin(mode);
};

void NL::OpenGL::End()
{
	glEnd();
};

void NL::OpenGL::SetVertexStreamsCount(WORD vsc)
{
	vstreams.resize(vsc);
};

void NL::OpenGL::SetIndexStreamsCount(WORD isc)
{
	istreams.resize(isc);
};

void NL::OpenGL::SetVertexArray(WORD vstream,void *V)
{
	vstreams[vstream] = V;
};

void NL::OpenGL::SetVertexDeclaration(VertexDeclaration vd)
{
	VD = vd;
};

void NL::OpenGL::SetIndexArray(WORD istream,void *I)
{
	istreams[istream] = I;
};

void NL::OpenGL::SetIndexType(INDEX_TYPE it)
{
	itype = it;
};

void NL::OpenGL::DrawPrimitive(WORD vstream,size_t vertscount)
{
	std::vector<Math::Vector3> *v = (std::vector<Math::Vector3> *)vstreams[vstream];

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&(*v)[0]);

	glColor3ub(255,0,0);

	glDrawArrays(GL_TRIANGLES,0,(GLsizei)v->size());
};

void NL::OpenGL::DrawIndexedPrimitive(WORD vstream,WORD istream,size_t indscount)
{
	ApplyTransform();

	std::vector<Math::Vector3> *v = (std::vector<Math::Vector3> *)vstreams[vstream];

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&(*v)[0]);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT,0,&Normals[0]);

	std::vector<WORD> *i = (std::vector<WORD> *)istreams[istream];

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);*/

	glDrawElements(GL_TRIANGLES,(GLsizei)i->size(),GL_UNSIGNED_SHORT, &(*i)[0]);

	//////////////////////////////////////////////////////////////////////////
	glDisable(GL_TEXTURE_2D); // Убрать!!!
	//////////////////////////////////////////////////////////////////////////

	//glDisable(GL_CULL_FACE);
};

void NL::OpenGL::SetColor(unsigned char r,unsigned char g,unsigned char b)
{
	glColor3ub(r,g,b);
};

void NL::OpenGL::DrawVertex(float x,float y,float z)
{
	glVertex3f(x,y,z);
};

void NL::OpenGL::DrawText(const String &family,unsigned int size,const String &text)
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
};

//--------------------------------------------------------------------------------------
// Операции над матрицами и стеком

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

		// Добавь текстуру!
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

		// Добавь текстуру!
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

		// Добавь текстуру!

	default:
		{
			Matrix4x4 tmpm;
			return tmpm.Nil();
		}
	}
};

//--------------------------------------------------------------------------------------
// Текстуры

int  NL::OpenGL::LoadTexture(const String &filename)
{
	ilLoad(IL_TYPE_UNKNOWN,(const ILstring)filename.c_str());	
	//Получение кода ошибки
	int err = ilGetError();
	//Если код не равен нулю ош
	if (err != IL_NO_ERROR)
	{
		return -1;	
	}
	//Ширина изображения
	int width = ilGetInteger(IL_IMAGE_WIDTH); 
	//Выота изображения
	int height = ilGetInteger(IL_IMAGE_HEIGHT); 
	//Число байт на пиксель	
	int bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); 	
	//Размер памяти
	int size = width * height * bpp;
	//Память под массив
	unsigned char* data = new unsigned char[size];
	//Получение растровых данных
	unsigned char *copyData = ilGetData();
	//Копирование растровых данных
	memcpy(data, copyData, size);
	//Тип хранения данных
	unsigned int type;
	//переопределить тип для OpenGL
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
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
	gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, width, height, type, 
		GL_UNSIGNED_BYTE, data);		
	//Удаление ненужного массива
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

void NL::OpenGL::SetTexCoordArray(WORD vstream,void *V)
{
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, 0, &(*((std::vector<Math::Vector2> *)V))[0] );
};

//--------------------------------------------------------------------------------------
// Расширения

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

void *NL::OpenGL::GetProcAddress(const String &name)
{
#ifdef	_WIN32
	return wglGetProcAddress(name.c_str());
#else
	return (void *)glXGetProcAddressARB((const GLubyte *)name.c_str());
#endif
};

//--------------------------------------------------------------------------------------
// Шейдеры

void NL::OpenGL::SetCgShader(cgShader *shader)
{
	if(!shader) return;
	
	cgGLBindProgram(shader->CgProgram);
	cgGLEnableProfile(shader->CgVertexProfile);
};

void NL::OpenGL::CheckCgErrors()
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) 
	{
		log->AddLine(string,"red");

		exit(1);
	}
};

//--------------------------------------------------------------------------------------

void NL::OpenGL::BeginScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void NL::OpenGL::EndScene()
{
	glFlush();
};

void NL::OpenGL::Release()
{

};

void NL::OpenGL::ApplyTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((float *)&(ViewMatrix * mst.top()));

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((float *)&ProjectionMatrix);
};