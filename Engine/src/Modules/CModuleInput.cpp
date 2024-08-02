#include "Modules/CModuleInput.h"

#include "AApplication.h"
#include "Modules/CModuleWindow.h"

#include <GLFW/glfw3.h>

namespace Engine
{

bool CModuleInput::Update()
{
	if( glfwGetKey( application->mModuleWindow->GetWindow(), GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( application->mModuleWindow->GetWindow(), true );

	return true;
}

} // namespace Engine
