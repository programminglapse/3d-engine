#ifndef C_MODULE_RENDER_H
#define C_MODULE_RENDER_H

#include "AModule.h"
#include "CShader.h"
#include "CTexture.h"
#include "CModel.h"

namespace Engine
{

class CModuleRender : public AModule
{
public:
	CModuleRender();

	bool Init() override;
	bool Update() override;

	const CShader& GetShader() const;
	void DrawModel( const CModel& aModel ) const;

private:
	CShader mShader;
	unsigned int mVAO;
	unsigned int mEBO;
	CTexture mTexture;
	CModel mModel;
};

} // namespace Engine

#endif // C_MODULE_RENDER_H
