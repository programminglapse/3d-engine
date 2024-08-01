#include "AApplication.h"

namespace Engine
{

void AApplication::Run()
{
	for( auto& module : mModules )
		if( !module->Init() )
			return;

	bool play = true;
	while( play )
	{
		for( auto& module : mModules )
			if( !module->PreUpdate() )
				play = false;
		for( auto& module : mModules )
			if( !module->Update() )
				play = false;
		for( auto& module : mModules )
			if( !module->PostUpdate() )
				play = false;
	}

	for( auto& module : mModules )
		if( !module->Clear() )
			return;
}

} // namespace Engine
