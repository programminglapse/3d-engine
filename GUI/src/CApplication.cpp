#include "CApplication.h"

#include "Modules/CModuleWindow.h"
#include "Modules/CModuleInput.h"
#include "Modules/CModuleRender.h"

namespace GUI
{

CApplication::CApplication()
{
	CreateModules();
}

void CApplication::CreateModules()
{
	mModules.push_back( mModuleWindow = new Engine::CModuleWindow( "Editor", 1000, 1000 ) );
	mModules.push_back( mModuleInput = new Engine::CModuleInput() );
	mModules.push_back( mModuleRender = new Engine::CModuleRender() );
}

} // namespace GUI
