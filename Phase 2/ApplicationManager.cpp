#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\ZoomIn.h"
#include "Actions\ZoomOut.h"
#include "Actions\ChangeFigColor.h"
#include "Actions\ExitAction.h"
#include "Actions\SwitchToPlayMode.h"
#include "Actions\DeleteAction.h"
#include "Actions\SwitchToDrawMode.h"
#include "Actions\ResizeAction.h"
#include "Actions\CopyAction.h"
#include "Actions\PasteAction.h"
#include "Actions\CutAction.h"
#include "Actions\SelectAction.h"
#include "Actions\MultiSelectAction.h"
#include "Actions\SaveAction.h"
#include "Actions\MoveByDrag.h"
#include "Actions\LoadAction.h"
#include "Actions\RotateAction.h"
#include "Actions\ChangeBkgroundClr.h"
#include "Actions\ResizeByDrag.h"
#include "Actions\RotateByDrag.h"
#include "Actions\PickHide.h"
#include "Actions\ScrambleFind.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	FigCount = 0;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{

	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;

	case DRAW_LINE:
		pAct = new AddLineAction(this);
		break;

	case DRAW_CIRC:
		pAct = new AddCircleAction(this);
		break;

	case DRAW_TRI:
		pAct = new AddTriangleAction(this);
		break;

	case ZOOM_IN:
		pAct = new ZoomIn(this);
		break;

	case ZOOM_OUT:
		pAct = new ZoomOut(this);
		break;

	case CHNG_DRAW_CLR:
		pAct = new ChangeFigColor(this);
		break;

	case TO_PLAY:
		pAct = new SwitchToPlayMode(this);
		break;

	case TO_DRAW:
		pAct = new SwitchToDrawMode(this);
		break;

	case DEL:
		pAct = new DeleteAction(this);
		break;

	case RESIZE:
		pAct = new ResizeAction(this);
		break;

	case SAVE:
		pAct = new SaveAction(this);
		break;

	case LOAD:
		pAct = new LoadAction(this);
		break;

	case COPY:
		pAct = new CopyAction(this);
		break;

	case CUT:
		pAct = new CutAction(this);
		break;

	case PASTE:
		pAct = new PasteAction(this);
		break;

	case EXIT:
		pAct = new ExitAction(this);
		break;

	case SELECT:
		pAct = new SelectAction(this);
		break;

	case MULTI_SELECT:
		pAct = new MultiSelectAction(this);
		break;

	case MOVE_DRAG:
		pAct = new MoveByDrag(this);
		break;

	case ROTATE:
		pAct = new RotateAction(this);
		break;

	case CHNG_BK_CLR:
		pAct = new ChangeBkgroundClr(this);
		break;

	case RESIZE_DRAG:
		pAct = new ResizeByDrag(this);
		break;

	case ROTATE_DRAG:
		pAct = new RotateByDrag(this);
		break;

	case PICK:
		pAct = new PickHide(this);
		break;

	case SCRAMBLE_FIND:
		pAct = new ScrambleFind(this);
		break;

	case STATUS:	//a click on the status bar ==> no action
		return;

	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::removeFigure(int ID) {
	bool found = false;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] && FigList[i]->getID() == ID)
		{
			found = true;
			delete FigList[i];
			FigList[i] = NULL;
			break;
		}
	}
	if (found)
	{
		fixFigList();
		FigCount--;
	}

}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::fixFigList() {
	for (int i = 0; i < FigCount - 1; i++)
		if (FigList[i] == NULL)
			swap(FigList[i], FigList[i + 1]);
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//traverse from the end, because last drawed is on top
	for (int i = FigCount - 1; i >= 0; i--)
		if (FigList[i]->isClicked(x, y))
			return FigList[i];

	return NULL; //didn't find any
}
//////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int index) const
{
	if (index < FigCount)
		return FigList[index];

	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y, CFigure** figures) const
{
	//traverse from the end, because last drawed is on top
	for (int i = FigCount - 1; i >= 0; i--)
		if (figures[i]->isClicked(x, y))
			return figures[i];

	return NULL; //didn't find any
}
void ApplicationManager::restartApp()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	FigCount = 0;
	pData->destroyClipBoard();
}
//////////////////////////////////////////////////////////////////////////////////
//Returns number of figures
int ApplicationManager::GetFigureCount() const
{
	return FigCount;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
	pOut->UpdateWindow();
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all figures for play mode on the user interface for play mode scramble and find mode
void ApplicationManager::UpdateInterface(CFigure** figures) const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
		figures[i]->Draw(pOut);
	}
	pOut->UpdateWindow();
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	pData->destroyClipBoard(); //if the program is over and clipboard still has data
}

//Changes the color of selected objects if no selected figures return false
bool ApplicationManager::ChangeSelectedColor(GfxInfo selectedColor)
{
	bool foundSelected = false;
	for (int i = 0; i < FigCount; i++)//changing the colors of selected objects
	{//if none found assign the flag found selectd to false
		CFigure *curr = FigList[i];
		if (curr->IsSelected()) {
			foundSelected = true;
			curr->ChngDrawClr(selectedColor.DrawClr);
			curr->ChngFillClr(selectedColor.FillClr);
			curr->ChngBrdrWidth(selectedColor.BorderWdth);
		}
	}
	return foundSelected;
}

void ApplicationManager::SelectAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetSelected(true);
	}
}

void ApplicationManager::DeSelectAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetSelected(false);
	}
}

void ApplicationManager::ShowAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->setVisible(true);
	}
}

void ApplicationManager::HideAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->setVisible(false);
	}
}
//scales the figures tohalf the screen
void ApplicationManager::ToLeftHalf() {

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->setCurrCordTemp();
		FigList[i]->Resize(0.5);
		FigList[i]->Move(-FigList[i]->getOriginXpos() / 2, 0);
	}
}

//Randomize the positions of figures to the right half of the screen
void ApplicationManager::RandomizePositionsRight(CFigure** figures) {

	for (int i = 0; i < FigCount; i++)
	{
		int randomX, randomY;

		randomX = rand() % ((UI.width / 2 - figures[i]->getWidth())) + (UI.width / 2) + figures[i]->getWidth() / 2 - figures[i]->getOriginXpos();

		randomY = rand() % (UI.height - UI.ToolBarHeight - figures[i]->getHeight()) - figures[i]->getOriginYpos() + UI.ToolBarHeight + figures[i]->getHeight() / 2;

		figures[i]->Move(randomX, randomY);
	}
}

//scales the figures to full the screen
void ApplicationManager::RestoreFromHalf() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->setTempCord();
	}
	if (FigCount > 0) {
		CFigure::setCount(ceil(CFigure::getCount() / 2));
	}
}

//delete figure array
void ApplicationManager::deleteFigureArray(CFigure** figures) {
	for (int i = 0; i < FigCount; i++)
	{
		delete figures[i];
	}
	delete[] figures;
}
//Create a copy of the figure array and return it
CFigure** ApplicationManager::createCopyOfFigures() {

	CFigure** figures = new CFigure*[FigCount];

	for (int i = 0; i < FigCount; i++)
	{
		figures[i] = FigList[i]->copyClone();
		figures[i]->setID(FigList[i]->getID());
	}
	return figures;
}
//returns a random visible figure and select it
CFigure* ApplicationManager::getRandomFigure() {
	int randomId;
	do {
		randomId = rand() % (FigCount);
	} while (!FigList[randomId]->isVisible());
	FigList[randomId]->SetSelected(true);
	return FigList[randomId];
}