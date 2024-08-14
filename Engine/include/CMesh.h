#ifndef C_MESH__H
#define C_MESH__H

#include "CTexture.h"

#include "glm/glm.hpp"

#include <vector>

namespace Engine
{

struct SVertex
{
	glm::vec3 mPosition;
	glm::vec3 mNormal;
	glm::vec2 mTextCoords;
    glm::vec3 mTangent;
    glm::vec3 mBitangent;
};

class CMesh
{
public:
	CMesh( const std::vector<SVertex>& aVertices, const std::vector<unsigned int>& aIndices,
			const std::vector<CTexture>& aTextures );

	const std::vector<SVertex>& GetVertices() const;
	const std::vector<unsigned int>& GetIndices() const;
	const std::vector<CTexture>& GetTextures() const;

	const unsigned int& GetVAO() const;
	const unsigned int& GetVBO() const;
	const unsigned int& GetEBO() const;

private:
	std::vector<SVertex> mVertices;
	std::vector<unsigned int> mIndices;
	std::vector<CTexture> mTextures;

	unsigned int mVAO;
	unsigned int mVBO;
	unsigned int mEBO;
};

} // namespace Engine

#endif // C_MESH__H
