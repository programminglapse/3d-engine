#ifndef C_APPLICATION__H
#define C_APPLICATION__H

#include "AApplication.h"

namespace GUI
{

class CApplication : public Engine::AApplication
{
public:
	CApplication();

	void CreateModules() override;
};

} // namespace GUI

#endif // C_APPLICATION__H
