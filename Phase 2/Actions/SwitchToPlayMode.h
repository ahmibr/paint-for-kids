#pragma once

#include"Action.h"
class SwitchToPlayMode :public Action
{
	
public:
	SwitchToPlayMode(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~SwitchToPlayMode();
	void Undo();
	void Redo();
};

