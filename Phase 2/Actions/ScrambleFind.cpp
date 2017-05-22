#include "ScrambleFind.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"


ScrambleFind::ScrambleFind(ApplicationManager * pApp) :Action(pApp)
{
	validCount = 0;
	inValidCount = 0;
}


ScrambleFind::~ScrambleFind()
{
}

//The game logic happens here
void ScrambleFind::Execute()
{
	pManager->DeSelectAllFigures();			//precatious act not needed except an error from other class occured
	Output* pOut = pManager->GetOutput();

	FiguresMaxID = CFigure::getCount(); //save it to restore after finish

	pManager->ToLeftHalf();								//shrinks figures to left half of screen
	gameFigures = pManager->createCopyOfFigures();		//create copy of images
	pManager->RandomizePositionsRight(gameFigures);		//randomize their positions in the right of screen
	pManager->UpdateInterface(gameFigures);				//over loaded function to draw original and copied images

	figuresCount = pManager->GetFigureCount();

	pOut->PrintMessage("Choose fugure like selected, Valide answers " + to_string(validCount) + ",	InValide answers " + to_string(inValidCount));

	//Main game loop
	while (validCount < figuresCount) {
		CFigure* Choice1;
		CFigure* Choice2;

		Choice1 = pManager->getRandomFigure();

		pManager->UpdateInterface(gameFigures);

		//getting the user chosen shape and if he chooses another action
		do {
			ReadActionParameters();
			Choice2 = selectedFigure;
		} while (Choice2 == NULL);

		//responsible of reinitializing process and start the loop from beginning
		if (restartGame)
		{
			RestartGame();
			pOut->PrintMessage("Game Restarted");
			continue;
		}

		//responsible for the breaking the loop only
		if (endGame)
		{
			break;
		}

		if (Choice2->getID() == Choice1->getID()) {
			Choice1->setVisible(false);
			Choice2->setVisible(false);
			validCount++;
		}
		else {
			Choice1->SetSelected(false);
			inValidCount++;
		}
		pOut->PrintMessage("Choose fugure like selected, Valide answers " + to_string(validCount) + ",	InValide answers " + to_string(inValidCount));
		pManager->UpdateInterface(gameFigures);
	}

	pOut->PrintMessage("Total grade = " + to_string(((float)validCount / (validCount + inValidCount)) * 100) + '%');

	//block of code responsible of getting the shapes as the game started
	pManager->ShowAllFigures();
	pManager->RestoreFromHalf();
	CFigure::setCount(FiguresMaxID); //restore everything
	pManager->deleteFigureArray(gameFigures);
	pManager->DeSelectAllFigures();
}

//the read action parameters are resbonsible for knowing the 
//selected figure from copied figures
//also determine if the user want to (End / Restart) game
void ScrambleFind::ReadActionParameters()
{
	int x, y;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	restartGame = endGame = false;

	pIn->GetPointClicked(x, y);

	if (y < UI.ToolBarHeight) {
		if (x / UI.MenuItemWidth == ITM_Find) {
			restartGame = true;
			return;
		}
		else if (x / UI.MenuItemWidth <= ITM_EXIT2) {
			endGame = true;
			return;
		}
	}

	selectedFigure = pManager->GetFigure(x, y, gameFigures);
}

//procedures of restarting the game is
//to get scores to zero
//show copied figures then randomize their place again
//delete the array of copied figures
void ScrambleFind::RestartGame()
{
	validCount = 0;
	inValidCount = 0;

	pManager->ShowAllFigures();
	pManager->deleteFigureArray(gameFigures);
	pManager->DeSelectAllFigures();

	gameFigures = pManager->createCopyOfFigures();

	pManager->RandomizePositionsRight(gameFigures);
	pManager->UpdateInterface(gameFigures);
}