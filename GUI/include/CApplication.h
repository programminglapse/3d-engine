#ifndef C_APPLICATION__H
#define C_APPLICATION__H

#include "AApplication.h"
#include "Modules/CModuleWindow.h"

namespace GUI
{

class CApplication : public Engine::AApplication
{
public:
	CApplication();

	void CreateModules() override;

private:
	Engine::CModuleWindow* mModuleWindow = nullptr;
};

} // namespace GUI

#endif // C_APPLICATION__H
