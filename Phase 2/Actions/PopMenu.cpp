#include "PopMenu.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


PopMenu::PopMenu(ApplicationManager *pApp) :Action(pApp)
{
}

void PopMenu::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	int x, y;
	pIn->GetPointClicked(x, y);

	if (x > menuCornerX && x < menuCornerX + UI.PopMenuWidth) {
		if (y > menuCornerY && y < menuCornerY + UI.PopMenuHeight) {
			action = (y - menuCornerY) / 50;
		}
	}

}

void PopMenu::Execute()
{
	ActionType procedureAction;

	procedureAction = SELECT;
	pManager->ExecuteAction(procedureAction);
	pManager->UpdateInterface();

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	menuCornerX = pIn->GetXmousePos();
	menuCornerY = pIn->GetYmousePos();

	if (UI.width - menuCornerX < UI.PopMenuWidth)
		menuCornerX -= UI.PopMenuWidth;
	if (UI.height - menuCornerY < UI.PopMenuHeight)
		menuCornerY -= UI.PopMenuHeight;

	pOut->DrawPopMenu(menuCornerX, menuCornerY);

	ReadActionParameters();

	switch (action)
	{
	case 0:
		procedureAction = DEL;
		break;
	case 1:
		procedureAction = COPY;
		break;
	case 2:
		procedureAction = CUT;
		break;
	case 3:
		procedureAction = PASTE;
		break;
	case 4:
		procedureAction = ROTATE;
		break;
	default:
		procedureAction = EMPTY;
		break;
	}

	pManager->ExecuteAction(procedureAction);

	pManager->DeSelectAllFigures();

}


PopMenu::~PopMenu()
{
}
