#include "DeleteAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"

DeleteAction::DeleteAction(ApplicationManager *pApp) :Action(pApp)
{
	confirm = false;

	Undoable = true;
}

void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();



	if (pIn->confirmAction("Delete"))
		confirm = true;
	else
		Undoable = false;
}
void DeleteAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (confirm) {
		deletedFigures = pManager->getSelectedList(deletedFigCount);
		deletedFigures = pManager->CreateAcopyArray(deletedFigures, deletedFigCount);

		if (!pManager->DeleteFigures())
			pOut->PrintMessage("You should select at least one figure to delete");
		else
			pOut->PrintMessage("Deletion is done.");
	}
}


DeleteAction::~DeleteAction()
{
}

void DeleteAction::Undo() {
	int tempMaxCount = CFigure::getCount();
	for (int i = 0; i < deletedFigCount; i++)
	{
		CFigure *deletionCopy = deletedFigures[i]->copyClone();
		deletionCopy->setID(deletedFigures[i]->getID());
		pManager->AddFigure(deletionCopy);
	}
	CFigure::setCount(tempMaxCount);

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("DeleteAction Undone");
}

void DeleteAction::Redo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < deletedFigCount; i++)
	{
		pManager->selectById(deletedFigures[i]->getID());
		delete deletedFigures[i];
	}

	deletedFigures = pManager->getSelectedList(deletedFigCount);
	deletedFigures = pManager->CreateAcopyArray(deletedFigures, deletedFigCount);

	for (int i = 0; i < deletedFigCount; i++)
	{
		pManager->removeFigure(deletedFigures[i]->getID());
	}

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("DeleteAction Redone");
}