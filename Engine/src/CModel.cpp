#include "CModel.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "glm/glm.hpp"
#include "stb/stb_image.h"

#include <iostream>

namespace Engine
{

CModel::CModel( const std::string& aPath ) :
	mPath( aPath ),
	mDirectory( mPath.substr( 0, mPath.find_last_of('/') ) )
{
	stbi_set_flip_vertically_on_load(true);
	LoadModel( mPath );
}

const std::vector<CMesh>& CModel::GetMeshes() const
{
	return mMeshes;
}

void CModel::LoadModel( const std::string& aPath )
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile( aPath, aiProcess_Triangulate | aiProcess_FlipUVs );

	if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	ProcessNode( scene->mRootNode, scene );
}

void CModel::ProcessNode( aiNode *node, const aiScene *scene )
{
	// process all the node's meshes (if any)
	for( unsigned int i = 0; i < node->mNumMeshes; i++ )
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		mMeshes.push_back( ProcessMesh( mesh, scene ) );
	}
	// then do the same for each of its children
	for( unsigned int i = 0; i < node->mNumChildren; i++ )
	{
		ProcessNode( node->mChildren[i], scene );
	}
}

CMesh CModel::ProcessMesh( aiMesh *mesh, const aiScene *scene )
{
	// data to fill
	std::vector<SVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<CTexture> textures;

	// walk through each of the mesh's vertices
	for( unsigned int i = 0; i < mesh->mNumVertices; i++ )
	{
		SVertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.mPosition = vector;
		// normals
		if( mesh->HasNormals() )
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.mNormal = vector;
		}
		// texture coordinates
		if( mesh->HasTextureCoords(0) ) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.mTextCoords = vec;

			if( mesh->HasTangentsAndBitangents() )
			{
				// tangent
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.mTangent = vector;
				// bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.mBitangent = vector;
			}
		}
		else
			vertex.mTextCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	std::vector<CTexture> diffuseMaps = LoadMaterialTextures( material, aiTextureType_DIFFUSE, "texture_diffuse" );
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<CTexture> specularMaps = LoadMaterialTextures( material, aiTextureType_SPECULAR, "texture_specular" );
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<CTexture> normalMaps = LoadMaterialTextures( material, aiTextureType_HEIGHT, "texture_normal" );
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<CTexture> heightMaps = LoadMaterialTextures( material, aiTextureType_AMBIENT, "texture_height" );
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return CMesh(vertices, indices, textures);
}

std::vector<CTexture> CModel::LoadMaterialTextures( aiMaterial *aMat, const aiTextureType& aType, const std::string& aTypeName )
{
	std::vector<CTexture> textures;
	for( unsigned int i = 0; i < aMat->GetTextureCount(aType); i++ )
	{
		aiString str;
		aMat->GetTexture(aType, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for(unsigned int j = 0; j < mTexturesLoaded.size(); j++)
		{
			if( mTexturesLoaded[j].GetPath() == mDirectory+"/"+str.C_Str() )
			{
				textures.push_back( mTexturesLoaded[j] );
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if(!skip)
		{   // if texture hasn't been loaded already, load it
			CTexture texture( mDirectory+"/"+str.C_Str() );
			texture.SetType( aTypeName );
			textures.push_back(texture);
			mTexturesLoaded.push_back( texture );  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
		}
	}
	return textures;
}

} // namespace Engine
