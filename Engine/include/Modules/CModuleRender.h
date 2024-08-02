#ifndef C_MODULE_RENDER_H
#define C_MODULE_RENDER_H

#include "AModule.h"

namespace Engine
{

class CModuleRender : public AModule
{
public:
	CModuleRender() = default;

	bool Init() override;
	bool Update() override;

private:
	unsigned int mShaderProgram = 0;
	unsigned int mVAO = 0;
	unsigned int mEBO = 0;
};

} // namespace Engine

#endif // C_MODULE_RENDER_H
