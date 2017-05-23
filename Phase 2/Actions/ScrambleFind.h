#ifndef SCRAMBLE_AND_FIND
#define SCRAMBLE_AND_FIND

#include "Action.h"
#include "..\Figures\CFigure.h"

class ScrambleFind : public Action
{
	int validCount, inValidCount;

	CFigure *selectedFigure;		//the player chosen fig while game
	CFigure** gameFigures;			//the copy of figure list

	bool endGame;					//if the player chose to quit in game
	bool restartGame;				//if the player chose to restart a game

	int figuresCount;				//the number of figures to play with
	int FiguresMaxID;				//the number of max id before creating copies

public:
	ScrambleFind(ApplicationManager *pApp);
	~ScrambleFind();

	virtual void Execute();

	virtual void ReadActionParameters();

	void RestartGame();			//Procedures of restarting a game

	void Undo();

	void Redo();

};

#endif