#ifndef C_MODULE_INPUT__H
#define C_MODULE_INPUT__H

#include "AModule.h"

namespace Engine
{

class CModuleInput : public AModule
{
public:
	CModuleInput() = default;

	bool Update() override;
};

} // namespace Engine

#endif // C_MODULE_INPUT__H
