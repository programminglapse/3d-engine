#include <iostream>

#include "CApplication.h"

Engine::AApplication* application;

int main()
{
	application = new GUI::CApplication();
	application->Run();

	return 0;
}
