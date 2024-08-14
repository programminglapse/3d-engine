#include "CMesh.h"

#include "glad/glad.h"

namespace
{

void SetUpMesh( unsigned int& aVAO, unsigned int& aVBO, unsigned int& aEBO,
		const std::vector<Engine::SVertex>& aVertices, const std::vector<unsigned int>& aIndices );

} // anonymous namespace

namespace Engine
{

CMesh::CMesh( const std::vector<SVertex>& aVertices, const std::vector<unsigned int>& aIndices,
			const std::vector<CTexture>& aTextures ) :
	mVertices( aVertices ),
	mIndices( aIndices ),
	mTextures( aTextures )
{
	SetUpMesh( mVAO, mVBO, mEBO, mVertices, mIndices );
}

const std::vector<SVertex>& CMesh::GetVertices() const
{
	return mVertices;
}

const std::vector<unsigned int>& CMesh::GetIndices() const
{
	return mIndices;
}

const std::vector<CTexture>& CMesh::GetTextures() const
{
	return mTextures;
}

const unsigned int& CMesh::GetVAO() const
{
	return mVAO;
}

const unsigned int& CMesh::GetVBO() const
{
	return mVBO;
}

const unsigned int& CMesh::GetEBO() const
{
	return mEBO;
}

} // namespace Engine

namespace
{

void SetUpMesh( unsigned int& aVAO, unsigned int& aVBO, unsigned int& aEBO,
		const std::vector<Engine::SVertex>& aVertices, const std::vector<unsigned int>& aIndices )
{
	glGenVertexArrays( 1, &aVAO );
	glGenBuffers( 1, &aVBO );
	glGenBuffers( 1, &aEBO );

	glBindVertexArray( aVAO );
	glBindBuffer( GL_ARRAY_BUFFER, aVBO );

	glBufferData( GL_ARRAY_BUFFER, aVertices.size() * sizeof(Engine::SVertex), &aVertices[0], GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, aEBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, aIndices.size() * sizeof(unsigned int),
				 &aIndices[0], GL_STATIC_DRAW );

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Engine::SVertex), (void*)0 );
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof(Engine::SVertex), (void*)offsetof(Engine::SVertex, mNormal) );
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof(Engine::SVertex), (void*)offsetof(Engine::SVertex, mTextCoords) );

	glBindVertexArray(0);
}

} // anonymous namespace
