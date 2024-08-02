#include "Modules/CModuleRender.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace
{

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

unsigned int CreateShader( const GLenum& aShaderType, const char *aShaderSource );
unsigned int CreateShaderProgram( unsigned int aVertexShader, unsigned int aFragmentShader );

bool CheckShader( unsigned int aShader );
bool CheckShaderProgram( unsigned int aShaderProgram );

unsigned int CreateVAO();
unsigned int CreateEBO();

} // anonymous namespace

namespace Engine
{

bool CModuleRender::Init()
{
	const auto vertexShader = CreateShader( GL_VERTEX_SHADER, vertexShaderSource );
	const auto fragmentShader = CreateShader( GL_FRAGMENT_SHADER, fragmentShaderSource );

	if( !CheckShader(vertexShader) || !CheckShader(fragmentShader) )
		return false;

	mShaderProgram = CreateShaderProgram( vertexShader, fragmentShader );

	if( !CheckShaderProgram( mShaderProgram ) )
		return false;

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	mVAO = CreateVAO();
	mEBO = CreateEBO();

	return true;
}

bool CModuleRender::Update()
{
	glUseProgram( mShaderProgram );
	glBindVertexArray( mVAO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mEBO );

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray( 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	return true;
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
	glGetShaderiv( aShader, GL_LINK_STATUS, &success );
	return success;
}

unsigned int CreateShaderProgram( unsigned int aVertexShader, unsigned int aFragmentShader )
{
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, aVertexShader );
	glAttachShader( shaderProgram, aFragmentShader );
	glLinkProgram( shaderProgram );
	return shaderProgram;
}

bool CheckShaderProgram( unsigned int aShaderProgram )
{
	int success;
	glGetProgramiv( aShaderProgram, GL_LINK_STATUS, &success );
	return success;
}

unsigned int CreateVAO()
{
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	unsigned int VBO, VAO;
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	glBindVertexArray( VAO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	return VAO;
}

unsigned int CreateEBO()
{
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	return EBO;
}

} // anonymous namespace
