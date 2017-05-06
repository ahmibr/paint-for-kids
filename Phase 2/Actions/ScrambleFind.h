#ifndef SCRAMBLE_AND_FIND
#define SCRAMBLE_AND_FIND

#include "Action.h"

class ScrambleFind : public Action
{
	int validCount, inValidCount;
public:
	ScrambleFind(ApplicationManager *pApp);
	~ScrambleFind();

	virtual void Execute();

	virtual void ReadActionParameters();


};

#endif