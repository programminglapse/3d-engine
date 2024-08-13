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
	const int GetWidth() const;
	const int GetHeight() const;

private:
	std::string mName;
	int mWidth;
	int mHeight;
	GLFWwindow* mWindow;
};

} // namespace Engine

#endif // C_MODULE_WINDOW__H
