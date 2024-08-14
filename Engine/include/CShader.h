#ifndef C_SHADER__H
#define C_SHADER__H

#include <string>
#include "glm/glm.hpp"

namespace Engine
{

class CShader
{
public:
	CShader();

	const unsigned int& GetID() const;

	bool IsValid() const;
	void Use() const;
	void SetMat4( const std::string& aName, const glm::mat4& aMat4 ) const;
	void SetInt( const std::string& aName, int aValue ) const;

private:
	unsigned int mID;
};

} // namespace Engine

#endif // C_SHADER__H
