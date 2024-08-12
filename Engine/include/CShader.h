#ifndef C_SHADER__H
#define C_SHADER__H

namespace Engine
{

class CShader
{
public:
	CShader();

	const unsigned int& GetID() const;

	bool IsValid() const;
	void Use() const;

private:
	unsigned int mID;
};

} // namespace Engine

#endif // C_SHADER__H
