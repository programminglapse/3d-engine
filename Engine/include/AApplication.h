#ifndef A_APLICATION__H
#define A_APLICATION__H

#include "Modules/AModule.h"

#include <vector>

namespace Engine
{

class CModuleWindow;
class CModuleInput;

class AApplication
{
public:
	virtual void CreateModules() = 0;

	void Run();

	CModuleWindow* mModuleWindow = nullptr;
	CModuleInput* mModuleInput = nullptr;

protected:
	std::vector<AModule*> mModules;
};

} // namespace Engine

extern Engine::AApplication* application;

#endif // A_APLICATION__H
