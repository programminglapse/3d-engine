#ifndef C_APPLICATION__H
#define C_APPLICATION__H

#include "AApplication.h"
#include "CModuleEditorCamera.h"

class CModuleEditorCamera;

namespace GUI
{

class CApplication : public Engine::AApplication
{
public:
	CApplication();

	void CreateModules() override;

	CModuleEditorCamera* mModuleEditorCamera = nullptr;
};

} // namespace GUI

#endif // C_APPLICATION__H
