#include "ApplicationManager.h"
#include "AllActions.h"

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
	selectedList = NULL;
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

	case PICK:
		pAct = new PickHide(this);
		break;

	case SCRAMBLE_FIND:
		pAct = new ScrambleFind(this);
		break;

	case ZOOM_NOT_SUPPORTED:
		pOut->PrintMessage("Not supported while zoom");
		break;

	case POP_MENU:
		pAct = new PopMenu(this);
		break;

	case STATUS:	//a click on the status bar ==> no action
		pOut->createCreditsWindow();
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

	x = (-UI.width / 2 + x) / (UI.zoomFactor) + UI.width / 2;
	y = (-UI.height / 2 + y) / (UI.zoomFactor) + UI.height / 2;

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
//////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SelectAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetSelected(true);
	}
}
//////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeSelectAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetSelected(false);
	}
}
//////////////////////////////////////////////////////////////////////////////////

//==================================================================================//
//								selected figures related							//
//==================================================================================//
CFigure ** ApplicationManager::getSelectedList(int & size)
{
	size = 0;
	if (selectedList) //if it has values before
		delete[] selectedList;
	selectedList = NULL;

	size = getSelectedCount();

	if (size)
	{
		selectedList = new CFigure*[size];
		for (int i = 0, j = 0; i < FigCount; i++)
			if (FigList[i]->IsSelected())
				selectedList[j++] = FigList[i];
	}
	return selectedList;
}
//////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::getSelectedCount() const
{
	int size = 0;
	for (int i = 0; i < FigCount; i++) //count number of selected elements
		if (FigList[i]->IsSelected())
			size++;
	return size;
}
//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::ResizeFigures(float resize)
{
	bool selected = false; // found selected element

	for (int i = 0; i < GetFigureCount(); i++)
	{
		CFigure *curr = FigList[i];
		if (curr->IsSelected()) {
			selected = true;
			curr->Resize(resize);
		}
	}
	return selected;
}
//////////////////////////////////////////////////////////////////////////////////

bool ApplicationManager::RotateFigures(float rotate)
{
	bool selected = false;// found selected element
	for (int i = 0; i < GetFigureCount(); i++)
	{
		CFigure *curr = FigList[i];
		if (curr->IsSelected()) {
			selected = true;
			curr->Rotate(rotate);
		}
	}
	return selected;
}
//////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::moveFigures(int dx, int dy)
{
	for (int i = 0; i < FigCount; i++)
	{
		CFigure *curr = FigList[i];
		if (curr->IsSelected()) {
			curr->Move(dx, dy);
		}
	}
}
//==================================================================================//
//								Play mode related Functions							//
//==================================================================================//
//get figure from a specific figure list
CFigure *ApplicationManager::GetFigure(int x, int y, CFigure** figures) const
{
	//traverse from the end, because last drawed is on top
	for (int i = FigCount - 1; i >= 0; i--)
		if (figures[i]->isClicked(x, y))
			return figures[i];

	return NULL; //didn't find any
}
//Draw all figures for play mode on the user interface for play mode scramble and find mode	-BM
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
void ApplicationManager::ShowAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->setVisible(true);
	}
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::HideAllFigures() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->setVisible(false);
	}
}
////////////////////////////////////////////////////////////////////////////////////
//scales the figures to half the screen
void ApplicationManager::ToLeftHalf() {

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->setCurrCordTemp();
		FigList[i]->Resize(0.5);
		FigList[i]->Move(-FigList[i]->getOriginXpos() / 2.0, 0);
	}
}
////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////
//scales the figures to full the screen
void ApplicationManager::RestoreFromHalf() {
	for (int i = 0; i < FigCount; i++)
		FigList[i]->setTempCord();

}
////////////////////////////////////////////////////////////////////////////////////
//delete figure array
void ApplicationManager::deleteFigureArray(CFigure** figures) {
	for (int i = 0; i < FigCount; i++)
	{
		delete figures[i];
	}
	delete[] figures;
}
////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////
//returns a random visible figure and select it
CFigure* ApplicationManager::getRandomFigure() {
	int randomId;
	do {
		randomId = rand() % (FigCount);
	} while (!FigList[randomId]->isVisible());
	FigList[randomId]->SetSelected(true);
	return FigList[randomId];
}
////////////////////////////////////////////////////////////////////////////////////
//returns number of figures with same type as reference figure
int ApplicationManager::NumberOfFigureOfType(CFigure* refrenceFigure) {
	int figures = 0;
	CFigure* fig;
	for (int i = 0; i < FigCount; i++)
	{
		fig = FigList[i];
		if (fig->getType() == refrenceFigure->getType())
			figures++;
	}
	return figures;
}
////////////////////////////////////////////////////////////////////////////////////
//returns number of figures with same color as reference figure
int ApplicationManager::NumberOfFigureOfColor(CFigure* refrenceFigure) {
	int figures = 0;
	CFigure* fig;
	for (int i = 0; i < FigCount; i++)
	{
		fig = FigList[i];
		if (fig->getFillClrName() == refrenceFigure->getFillClrName())
			figures++;
	}
	return figures;
}
////////////////////////////////////////////////////////////////////////////////////
//returns number of figures with same type and color as reference figure
int ApplicationManager::NumberOfFigureOfColorAndType(CFigure* refrenceFigure) {
	int figures = 0;
	CFigure* fig;
	for (int i = 0; i < FigCount; i++)
	{
		fig = FigList[i];
		if (fig->getType() == refrenceFigure->getType() && fig->getFillClrName() == refrenceFigure->getFillClrName())
			figures++;
	}
	return figures;
}
////////////////////////////////////////////////////////////////////////////////////
//returns largest area in figures
float ApplicationManager::LargestArea() {
	float area = 0;
	CFigure* fig;
	for (int i = 0; i < FigCount; i++)
	{
		fig = FigList[i];
		if (fig->isVisible())
		{
			if (area < fig->getArea())
				area = fig->getArea();
		}
	}
	return area;
}
////////////////////////////////////////////////////////////////////////////////////

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
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}

//////////////////////////////////////////////////////////////////////////////////
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
	if (selectedList)
		delete[] selectedList;
	pData->destroyClipBoard(); //if the program is over and clipboard still has data
}