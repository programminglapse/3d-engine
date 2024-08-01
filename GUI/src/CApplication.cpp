#include "CApplication.h"

namespace GUI
{

CApplication::CApplication()
{
	CreateModules();
}

void CApplication::CreateModules()
{
	mModules.push_back( mModuleWindow = new Engine::CModuleWindow( "Editor", 1000, 1000 ) );
}

} // namespace GUI
