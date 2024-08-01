#ifndef A_APLICATION__H
#define A_APLICATION__H

#include "Modules/AModule.h"

#include <vector>

namespace Engine
{

class AApplication
{
public:
	virtual void CreateModules() = 0;

	void Run();

protected:
	std::vector<AModule*> mModules;
};

} // namespace Engine

#endif // A_APLICATION__H
