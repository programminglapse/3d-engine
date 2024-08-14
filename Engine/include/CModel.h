#ifndef C_MODEL__H
#define C_MODEL__H

#include "CTexture.h"
#include "CMesh.h"

#include "assimp/scene.h"

#include <string>
#include <vector>

namespace Engine
{

class CModel
{
public:
	CModel( const std::string& aPath );

	const std::vector<CMesh>& GetMeshes() const;

private:
	void LoadModel( const std::string& aPath );
	void ProcessNode( aiNode *node, const aiScene *scene );
	CMesh ProcessMesh( aiMesh *mesh, const aiScene *scene );
	std::vector<CTexture> LoadMaterialTextures( aiMaterial *aMat, const aiTextureType& aType, const std::string& aTypeName );

	std::vector<CMesh> mMeshes;
	std::string mPath;
	std::vector<CTexture> mTexturesLoaded;
	std::string mDirectory;
};

} // namespace Engine

#endif
