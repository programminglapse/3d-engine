#include "Modules/CModuleRender.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace
{

unsigned int CreateVAO();
unsigned int CreateEBO();

} // anonymous namespace

namespace Engine
{

CModuleRender::CModuleRender() :
	mVAO( CreateVAO() ),
	mEBO( CreateEBO() ),
	mTexture( "../Engine/resources/textures/wall.jpg" )
{
}

bool CModuleRender::Init()
{
	return mShader.IsValid();
}

bool CModuleRender::Update()
{
	mShader.Use();
	mTexture.Bind();

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

unsigned int CreateVAO()
{
	const float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

	unsigned int VBO, VAO;
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	glBindVertexArray( VAO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
	glEnableVertexAttribArray(1);
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)) );
	glEnableVertexAttribArray(2);

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
