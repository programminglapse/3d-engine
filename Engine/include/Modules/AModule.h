#ifndef A_MODULE__H
#define A_MODULE__H

namespace Engine
{

class AModule
{
public:
	virtual bool Init(){ return true; }
	virtual bool PreUpdate(){ return true; }
	virtual bool Update() = 0;
	virtual bool PostUpdate(){ return true; }
	virtual bool Clear(){ return true; }
};

} // namespace Engine

#endif // A_MODULE__H
