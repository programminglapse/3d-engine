#include "Modules/CModuleWindow.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace
{

void InitGLFW();
GLFWwindow* CreateWindow( const std::string& aName, const int aWidth, const int aHeight );
void FramebufferSizeCallback( GLFWwindow* aWindow, const int aWidth, const int aHeight);

} // anonymous namespace

namespace Engine
{

CModuleWindow::CModuleWindow( const std::string& aName, const int aWidth, const int aHeight ) :
	mName( aName ),
	mWidth( aWidth ),
	mHeight( aHeight )
{
}

bool CModuleWindow::Init()
{
	InitGLFW();
	mWindow = CreateWindow( mName, mWidth, mHeight );

	if( mWindow == nullptr )
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent( mWindow );
	glfwSetFramebufferSizeCallback( mWindow, FramebufferSizeCallback );

	if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
		return false;

	return true;
}

bool CModuleWindow::PreUpdate()
{
	glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	return true;
}

bool CModuleWindow::Update()
{
	return !glfwWindowShouldClose( mWindow );
}

bool CModuleWindow::PostUpdate()
{
	glfwSwapBuffers( mWindow );
	glfwPollEvents();

	return true;
}

bool CModuleWindow::Clear()
{
	glfwTerminate();
	mWindow = nullptr;

	return true;
}

GLFWwindow* CModuleWindow::GetWindow()
{
	return mWindow;
}

} // namespace Engine

namespace
{

void InitGLFW()
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* CreateWindow( const std::string& aName, const int aWidth, const int aHeight )
{
	return glfwCreateWindow( aWidth, aHeight, aName.c_str(), nullptr, nullptr );;
}

void FramebufferSizeCallback( GLFWwindow* aWindow, const int aWidth, const int aHeight)
{
	glViewport( 0, 0, aWidth, aHeight);
}

} // anonymous namespace
