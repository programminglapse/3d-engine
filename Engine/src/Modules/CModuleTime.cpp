#include "CModuleTime.h"

#include <GLFW/glfw3.h>

namespace Engine
{

bool CModuleTime::Update()
{
	const auto currentTime = static_cast<float>(glfwGetTime());
	mDeltaTime = currentTime - mLastTime;
	mLastTime = currentTime;

	return true;
}

} // namespace Engine
