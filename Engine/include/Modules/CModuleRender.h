#ifndef C_MODULE_RENDER_H
#define C_MODULE_RENDER_H

#include "AModule.h"
#include "CShader.h"
#include "CTexture.h"

namespace Engine
{

class CModuleRender : public AModule
{
public:
	CModuleRender();

	bool Init() override;
	bool Update() override;

private:
	CShader mShader;
	unsigned int mVAO;
	unsigned int mEBO;
	CTexture mTexture;
};

} // namespace Engine

#endif // C_MODULE_RENDER_H
