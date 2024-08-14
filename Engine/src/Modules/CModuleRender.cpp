#include "Modules/CModuleRender.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "assimp/Importer.hpp"
#include <iostream>
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
	mTexture( "../Engine/resources/textures/wall.jpg" ),
	mModel( "../Engine/resources/model/backpack.obj" )
{
}

bool CModuleRender::Init()
{
	return mShader.IsValid();
}

bool CModuleRender::Update()
{
	mShader.Use();
	DrawModel( mModel );
	/*mTexture.Bind();

	glBindVertexArray( mVAO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mEBO );

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray( 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
*/
	return true;
}

const CShader& CModuleRender::GetShader() const
{
	return mShader;
}

void CModuleRender::DrawModel( const CModel& aModel ) const
{
	for( const auto& aMesh : aModel.GetMeshes() )
	{
		// bind appropriate textures
		unsigned int diffuseNr  = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr   = 1;
		unsigned int heightNr   = 1;

		for( unsigned int i = 0; i < aMesh.GetTextures().size(); i++ )
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = aMesh.GetTextures()[i].GetType();
			std::cout << name << std::endl;
			if(name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if(name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to string
			else if(name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to string
			else if(name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to string

			// now set the sampler to the correct texture unit
			mShader.SetInt( name + number, i );
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, aMesh.GetTextures()[i].GetID());
		}

		// draw mesh
		glBindVertexArray( aMesh.GetVAO() );
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(aMesh.GetIndices().size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}
}

} // namespace Engine

namespace
{

unsigned int CreateVAO()
{
	const float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
    };

	unsigned int VBO, VAO;
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	glBindVertexArray( VAO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0 );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)) );
	glEnableVertexAttribArray(1);

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
