#ifndef C_MODULE_WINDOW__H
#define C_MODULE_WINDOW__H

#include "AModule.h"

#include <string>

class GLFWwindow;

namespace Engine
{

class CModuleWindow : public AModule
{
public:
	CModuleWindow( const std::string& aName, const int aWidth, const int aHeight );

	bool Init() override;
	bool PreUpdate() override;
	bool Update() override;
	bool PostUpdate() override;
	bool Clear() override;

	GLFWwindow* GetWindow();

private:
	GLFWwindow* mWindow;
	std::string mName;
	int mWidth;
	int mHeight;
};

} // namespace Engine

#endif // C_MODULE_WINDOW__H
