#include "CModuleEditorCamera.h"

#include "CApplication.h"
#include "Modules/CModuleWindow.h"
#include "Modules/CModuleRender.h"
#include "Modules/CModuleTime.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace GUI
{

CModuleEditorCamera::CModuleEditorCamera() :
	mCamera( CreateCamera() )
{
}

bool CModuleEditorCamera::Init()
{
	mCamera.SetProjectionMatrix( glm::perspective( glm::radians(45.0f),
			(float)application->mModuleWindow->GetWidth() / (float)application->mModuleWindow->GetHeight(), 0.1f, 100.0f ) );

	application->mModuleRender->GetShader().Use();
	application->mModuleRender->GetShader().SetMat4( "projection", mCamera.GetProjectionMatrix() );
	application->mModuleRender->GetShader().SetMat4( "model", mCamera.GetModelMatrix() );
	application->mModuleRender->GetShader().SetMat4( "view", mCamera.GetViewMatrix() );

	return true;
}

bool CModuleEditorCamera::Update()
{
	HandleInput();
	application->mModuleRender->GetShader().SetMat4( "view", mCamera.GetViewMatrix() );

	return true;
}

void CModuleEditorCamera::HandleInput()
{
	glm::vec3 movement = glm::vec3(0.0f);
	if( glfwGetKey( application->mModuleWindow->GetWindow(), GLFW_KEY_A ) == GLFW_PRESS )
		movement.x -= application->mModuleTime->GetDeltaTime();
	if( glfwGetKey( application->mModuleWindow->GetWindow(), GLFW_KEY_D ) == GLFW_PRESS )
		movement.x += application->mModuleTime->GetDeltaTime();
	if( glfwGetKey( application->mModuleWindow->GetWindow(), GLFW_KEY_W ) == GLFW_PRESS )
		movement.y += application->mModuleTime->GetDeltaTime();
	if( glfwGetKey( application->mModuleWindow->GetWindow(), GLFW_KEY_S ) == GLFW_PRESS )
		movement.y -= application->mModuleTime->GetDeltaTime();
	if( glfwGetKey( application->mModuleWindow->GetWindow(), GLFW_KEY_Q ) == GLFW_PRESS )
		movement.z += application->mModuleTime->GetDeltaTime();
	if( glfwGetKey( application->mModuleWindow->GetWindow(), GLFW_KEY_E ) == GLFW_PRESS )
		movement.z -= application->mModuleTime->GetDeltaTime();

	mCamera.Move( movement );
}

Engine::CCamera CModuleEditorCamera::CreateCamera()
{
	return Engine::CCamera( glm::vec3( 0.0f, 0.0f, 3.0f ), glm::vec3( 0.0f, 0.0f, -1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ),
			glm::mat4( 1.0f ) );
}

} // namespace GUI
