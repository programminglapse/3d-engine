#ifndef C_MODULE_TIME_H
#define C_MODULE_TIME_H

#include "AModule.h"

namespace Engine
{

class CModuleTime : public AModule
{
public:
	CModuleTime() = default;

	bool Update() override;

	const float& GetDeltaTime() const;

private:
	float mDeltaTime = 0.0f;
	float mLastTime = 0.0f;
};

} // namespace Engine

#endif // C_MODULE_TIME_H
