#include "ResizeByDrag.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ResizeByDrag::ResizeByDrag(ApplicationManager * pApp) :Action(pApp)
{
	senstivity = 50;
	totalResize = 0;
}

ResizeByDrag::~ResizeByDrag()
{
	delete[] selectedFigsIds;
}

void ResizeByDrag::ReadActionParameters()
{

}

//Execute the action
void ResizeByDrag::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int xpos, ypos, lastXpos;//the current position of x,y and last pos
	float value;

	pOut->PrintMessage("Resizing selected objects.");

	pIn->GetPointClicked(xpos, ypos);
	lastXpos = xpos;//during the first frame xpos is the last

	selectedFigs = pManager->getSelectedList(selectedFigsCount);
	//selectedFigs = pManager->CreateAcopyArray(selectedFigs, selectedFigsCount);
	selectedFigsIds = pManager->getIdArray(selectedFigs, selectedFigsCount);

	while (xpos != -1) {

		dx = xpos - lastXpos;//dx is the change in x from current to last frame
		lastXpos = xpos;

		value = 1 + dx / senstivity;

		totalResize += value / 10.0;

		pManager->ResizeFigures(value);

		pIn->GetMouseMove(xpos, ypos);

		pManager->UpdateInterface();
	}

	pOut->ClearStatusBar();
}


void ResizeByDrag::Undo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	cout << totalResize << endl;

	pManager->ResizeFigures(1 / totalResize);
}

void ResizeByDrag::Redo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	pManager->ResizeFigures(totalResize);
}