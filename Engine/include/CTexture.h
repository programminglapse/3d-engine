#ifndef C_TEXTURE__H
#define C_TEXTURE__H

#include <string>

namespace Engine
{

class CTexture
{
public:
	CTexture( const std::string& aPath );

	void Bind() const;

	const unsigned int& GetID() const;
	const std::string& GetPath() const;
	const std::string& GetType() const;
	void SetType( const std::string& aType );

private:
	unsigned int mID;
	std::string mPath;
	std::string mType;
};

} // namespace Engine

#endif // C_TEXTURE__H
