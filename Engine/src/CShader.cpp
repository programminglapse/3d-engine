#include "CShader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace
{

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection*view*model*vec4( aPos.x, aPos.y, aPos.z, 1.0 );\n"
    "   TexCoord = vec2( aTexCoord.x, aTexCoord.y );\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture( texture1, TexCoord );\n"
    "}\n\0";

unsigned int CreateShader( const GLenum& aShaderType, const char *aShaderSource );
unsigned int CreateShaderProgram();

bool CheckShader( unsigned int aShader );

} // anonymous namespace

namespace Engine
{

CShader::CShader() :
	mID( CreateShaderProgram() )
{
}

const unsigned int& CShader::GetID() const
{
	return mID;
}

bool CShader::IsValid() const
{
	int success;
	glGetProgramiv( mID, GL_LINK_STATUS, &success );
	return success;
}

void CShader::Use() const
{
	glUseProgram( mID );
}

void CShader::SetMat4( const std::string& aName, const glm::mat4& aMat4 ) const
{
	glUniformMatrix4fv( glGetUniformLocation( mID, aName.c_str() ), 1, GL_FALSE, &aMat4[0][0]);
}

} // namespace Engine

namespace
{

unsigned int CreateShader( const GLenum& aShaderType, const char *aShaderSource )
{
	unsigned int shader = glCreateShader( aShaderType );
	glShaderSource( shader, 1, &aShaderSource, NULL );
	glCompileShader( shader );

	return shader;
}

bool CheckShader( unsigned int aShader )
{
	int success;
	glGetShaderiv( aShader, GL_COMPILE_STATUS, &success );
	return success;
}

unsigned int CreateShaderProgram()
{
	const auto vertexShader = CreateShader( GL_VERTEX_SHADER, vertexShaderSource );
	const auto fragmentShader = CreateShader( GL_FRAGMENT_SHADER, fragmentShaderSource );

	if( !CheckShader(vertexShader) || !CheckShader(fragmentShader) )
		return 0;

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	return shaderProgram;
}

} // anonymous namespace
