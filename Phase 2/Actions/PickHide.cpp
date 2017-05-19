#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\Cline.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "PickHide.h"

void PickHide::byType()
{
	/*for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		fig = pManager->GetFigure(i);
		if (fig->getType() == current->getType())
			figures++;
	}*/
	figures = pManager->NumberOfFigureOfType(current);
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (pickedFigures < figures)
	{
		pIn->GetPointClicked(x, y);
		choosenFig = pManager->GetFigure(x, y);
		if (choosenFig != NULL)
		{
			//if visible
			if (choosenFig->getType() == current->getType())
			{
				choosenFig->setVisible(false);
				vCount++;
				pickedFigures++;

			}
			else
			{
				invCount++;

			}
		}
		str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
		pOut->PrintMessage(str);
		pManager->UpdateInterface();
	}

}


void PickHide::byColor()
{
	/*for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		fig = pManager->GetFigure(i);
		if (fig->getFillClrName() == current->getFillClrName())
			figures++;
	}*/
	figures = pManager->NumberOfFigureOfColor(current);
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (pickedFigures < figures)
	{
		pIn->GetPointClicked(x, y);
		choosenFig = pManager->GetFigure(x, y);
		if (choosenFig != NULL)
		{
			//if visible
			if (choosenFig->getFillClrName() == current->getFillClrName())
			{
				choosenFig->setVisible(false);
				vCount++;
				pickedFigures++;
			}
			else
			{
				invCount++;
			}
		}
		str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
		pOut->PrintMessage(str);
		pManager->UpdateInterface();
	}
}

void PickHide::byType_Color()
{
	/*for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		fig = pManager->GetFigure(i);
		if (fig->getType() == current->getType() && fig->getFillClrName() == current->getFillClrName())
			figures++;
	}*/
	figures = pManager->NumberOfFigureOfColorAndType(current);
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (pickedFigures < figures)
	{
		pIn->GetPointClicked(x, y);
		choosenFig = pManager->GetFigure(x, y);
		if (choosenFig != NULL)
		{
			//if visible
			if (choosenFig->getType() == current->getType() && choosenFig->getFillClrName() == current->getFillClrName())
			{
				choosenFig->setVisible(false);
				vCount++;
				pickedFigures++;
			}
			else
			{
				invCount++;
			}
		}
		str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
		pOut->PrintMessage(str);
		pManager->UpdateInterface();
	}
}

void PickHide::byArea()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (pickedFigures < pManager->GetFigureCount())
	{
		float area = pManager->LargestArea();
		/*for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			current = pManager->GetFigure(i);
			if (current->isVisible())
			{
				if (area < current->getArea())
					area = current->getArea();
			}
		}*/
		pIn->GetPointClicked(x, y);
		choosenFig = pManager->GetFigure(x, y);
		if (choosenFig != NULL)
		{
			if (fabs(choosenFig->getArea() - area) < 1e-4)
			{
				choosenFig->setVisible(false);
				vCount++;
				pickedFigures++;
			}
			else
			{
				invCount++;
			}
		}
		str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
		pOut->PrintMessage(str);
		pManager->UpdateInterface();
	}
}

PickHide::PickHide(ApplicationManager * pApp) :Action(pApp)
{
	vCount = 0;
	invCount = 0;
	figures = 0;
	pickedFigures = 0;
	current = NULL;
	choosenFig = NULL;
}

void PickHide::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Pick and Hide mode");
	if (pManager->GetFigureCount() == 0)
		current = NULL;
	else {
		PickType = pIn->selectPickType();
		//current = pManager->GetFigure(rand() % pManager->GetFigureCount());
		current = pManager->getRandomFigure();
		current->SetSelected(false);
	}
}

//Execute the action
void PickHide::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	int figures = 0;
	int pickedFigures = 0;
	if (current != NULL) {
		switch (PickType)
		{
		case 1: //byType
			str = "Pick " + current->getType() + 's';
			pOut->PrintMessage(str);
			byType();
			str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
			pOut->PrintMessage(str);
			break;

		case 2: //byColor
			str = "Pick " + current->getFillClrName() + " figures";
			pOut->PrintMessage(str);
			byColor();
			str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
			pOut->PrintMessage(str);
			break;

		case 3: //byType_Color
			str = "Pick " + current->getFillClrName() + ' ' + current->getType() + 's';
			pOut->PrintMessage(str);
			byType_Color();
			str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
			pOut->PrintMessage(str);
			break;

		case 4: //byArea
			pOut->PrintMessage("click on figures from largest to smallest");
			byArea();
			str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
			pOut->PrintMessage(str);
			break;

		}
		pManager->ShowAllFigures();
	}
	else
		pOut->PrintMessage("Draw or load a graph first");
}
