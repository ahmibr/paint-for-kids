#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\Cline.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "PickHide.h"

bool PickHide::byType()
{
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(x, y);
	choosenFig = pManager->GetFigure(x, y);
	if (choosenFig != NULL)
	{
		//if visible
		if (choosenFig->getType() == current->getType())
		{
			choosenFig->setVisible(false);
			vCount++;
			return true;
		}
		else
		{
			invCount++;
			return false;
		}
	}
	return false;
}

bool PickHide::byColor()
{
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(x, y);
	choosenFig = pManager->GetFigure(x, y);
	if (choosenFig != NULL)
	{
		//if visible
		if (choosenFig->getFillClrName() == current->getFillClrName())
		{
			//hide
			choosenFig->setVisible(false);
			vCount++;
			return true;
		}
		else
		{
			invCount++;
			return false;
		}
	}
	return false;
}

bool PickHide::byType_Color()
{
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(x, y);
	choosenFig = pManager->GetFigure(x, y);
	if (choosenFig != NULL)
	{
		//if visible
		if (choosenFig->getType() == current->getType() && choosenFig->getFillClrName() == current->getFillClrName())
		{
			//hide
			choosenFig->setVisible(false);
			vCount++;
			return true;
		}
		else
		{
			invCount++;
			return false;
		}
	}
	return false;
}

bool PickHide::byArea()
{
	Input* pIn = pManager->GetInput();
	float area = 0;
	for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		current = pManager->GetFigure(i);
		if (current->isVisible())
		{
			if (area < current->getArea())
				area = current->getArea();
		}

	}
	pIn->GetPointClicked(x, y);
	choosenFig = pManager->GetFigure(x, y);
	if (choosenFig != NULL)
	{
		if (fabs(choosenFig->getArea() - area) < 1e-4)
		{
			//hide
			choosenFig->setVisible(false);
			vCount++;
			return true;
		}
		else
		{
			invCount++;
			return false;
		}
	}
	return false;
}

PickHide::PickHide(ApplicationManager * pApp) :Action(pApp)
{
	vCount = 0;
	invCount = 0;
	current = NULL;
	choosenFig = NULL;
}

void PickHide::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Pick and Hide mode");
	PickType = pIn->selectPickType();
	current = pManager->GetFigure(rand() % pManager->GetFigureCount());
}

//Execute the action
void PickHide::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	int figures = 0;
	int pickedFigures = 0;
	CFigure* fig;
	switch (PickType)
	{
	case 1: //byType
		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			fig = pManager->GetFigure(i);
			if (fig->getType() == current->getType())
				figures++;
		}
		str = "Pick " + current->getType(); +'s';
		pOut->PrintMessage(str);
		while (pickedFigures < figures)
		{
			if (byType())
				pickedFigures++;
			str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
		str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
		pOut->PrintMessage(str);
		break;

	case 2: //byColor
		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			fig = pManager->GetFigure(i);
			if (fig->getFillClrName() == current->getFillClrName())
				figures++;
		}
		str = "Pick " + current->getFillClrName() + " figures";
		pOut->PrintMessage(str);
		while (pickedFigures < figures)
		{
			if (byColor())
				pickedFigures++;
			str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
		str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
		pOut->PrintMessage(str);
		break;

	case 3: //byType_Color
		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			fig = pManager->GetFigure(i);
			if (fig->getType() == current->getType() && fig->getFillClrName() == current->getFillClrName())
				figures++;
		}
		str = "Pick " + current->getFillClrName() + ' ' + current->getType() + 's';
		pOut->PrintMessage(str);
		while (pickedFigures < figures)
		{
			if (byType_Color())
				pickedFigures++;
			str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
		str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
		pOut->PrintMessage(str);
		break;

	case 4: //byArea
		pOut->PrintMessage("click on figures from largest to smallest");
		while (pickedFigures < pManager->GetFigureCount())
		{
			if (byArea())
				pickedFigures++;
			str = "Valid picks = " + to_string(vCount) + " invalid picks = " + to_string(invCount);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
		str = "Total grade = " + to_string(((float)vCount / (vCount + invCount)) * 100) + '%';
		pOut->PrintMessage(str);
		break;
	}
	for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		pManager->GetFigure(i)->setVisible(true);
	}
}
