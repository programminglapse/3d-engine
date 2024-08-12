#include "CTexture.h"

#include "stb/stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace
{

unsigned int CreateTexture( const std::string& aPath );

} // anonymous namespace

namespace Engine
{

CTexture::CTexture( const std::string& aPath ) :
	mID( CreateTexture( aPath ) )
{
}

void CTexture::Bind() const
{
	glBindTexture( GL_TEXTURE_2D, mID );
}

} // namespace Engine

namespace
{

unsigned int CreateTexture( const std::string& aPath )
{
	unsigned int texture;
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	int width, height, nrChannels;
	unsigned char *data = stbi_load( aPath.c_str(), &width, &height, &nrChannels, 0 );
	if( data )
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );
	}
	stbi_image_free( data );

	return texture;
}

} // anonymous namespace
