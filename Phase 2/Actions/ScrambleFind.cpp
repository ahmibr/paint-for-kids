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

//Execute the action
void ScrambleFind::Execute()
{
	int x, y;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pManager->ToLeftHalf();
	pManager->UpdateInterface();

	CFigure** gameFigures = pManager->createCopyOfFigures();
	pManager->RandomizePositionsRight(gameFigures);
	pManager->UpdateInterface(gameFigures);


	int figuresCount = pManager->GetFigureCount();

	pOut->PrintMessage("Valide answers " + to_string(validCount) + ",	InValide answers " + to_string(inValidCount));

	while (validCount < figuresCount) {
		CFigure* Choice1;
		CFigure* Choice2;

		Choice1 = pManager->getRandomFigure();

		pManager->UpdateInterface(gameFigures);

		do {
			pIn->GetPointClicked(x, y);
			Choice2 = pManager->GetFigure(x, y, gameFigures);
		} while (Choice2 == NULL);

		if (Choice2->getID() == Choice1->getID()) {
			Choice1->setVisible(false);
			Choice2->setVisible(false);
			validCount++;
		}
		else {
			Choice1->SetSelected(false);
			inValidCount++;
		}
		pOut->PrintMessage("Valide answers " + to_string(validCount) + ",	InValide answers " + to_string(inValidCount));
		pManager->UpdateInterface(gameFigures);
	}

	pOut->PrintMessage("Total grade = " + to_string(((float)validCount / (validCount + inValidCount)) * 100) + '%');

	pManager->ShowAllFigures();
	pManager->RestoreFromHalf();
	pManager->deleteFigureArray(gameFigures);
	pManager->DeSelectAllFigures();
}

void ScrambleFind::ReadActionParameters()
{

}