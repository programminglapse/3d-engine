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

private:
	unsigned int mID;
};

} // namespace Engine

#endif // C_TEXTURE__H
