#ifndef __TEXTURE_OPEN_IL
#define __TEXTURE_OPEN_IL

#pragma warning (disable : 4996)
#undef _UNICODE

#include <stdlib.h>
#include <IL/il.h> //notice the OpenIL include



class	TextureOpenIL
{
public:
	static ILuint loadTexFile(const char* filename);
};

#endif
