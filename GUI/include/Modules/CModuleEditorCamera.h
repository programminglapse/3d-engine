#ifndef C_MODULE_EDITOR_CAMERA_H
#define C_MODULE_EDITOR_CAMERA_H

#include "Modules/AModule.h"
#include "CCamera.h"

namespace GUI
{

class CModuleEditorCamera : public Engine::AModule
{
public:
	CModuleEditorCamera();

	bool Init() override;
	bool Update() override;

private:
	void HandleInput();
	Engine::CCamera CreateCamera();

	Engine::CCamera mCamera;
};

} // namespace GUI

#endif // C_MODULE_EDITOR_CAMERA_H
