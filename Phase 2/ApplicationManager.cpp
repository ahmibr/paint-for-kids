#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\ZoomIn.h"
#include "Actions\ZoomOut.h"
#include "Actions\ChangeFigColor.h"
#include "Actions\ExitAction.h"
#include"Actions\SwitchToPlayMode.h"
#include"Actions\DeleteAction.h"
#include"Actions\SwitchToDrawMode.h"
#include"Actions\ResizeAction.h"
#include "Actions\CopyAction.h"
#include "Actions\PasteAction.h"

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
	
	case COPY:
		pAct = new CopyAction(this);
		break;

	case PASTE:
		pAct = new PasteAction(this);
		break;

	case EXIT:
		///create ExitAction here
		pAct = new ExitAction(this);
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
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	

	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int index) const
{
	if (index < FigCount)
		return FigList[index];

	return NULL;
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
