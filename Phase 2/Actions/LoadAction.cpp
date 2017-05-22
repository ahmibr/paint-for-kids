#include "LoadAction.h"

#include "..\ApplicationManager.h"

#include"..\Figures\CFigure.h"
#include"..\Figures\CCircle.h"
#include"..\Figures\Cline.h"
#include"..\Figures\CRectangle.h"
#include"..\Figures\CTriangle.h"



LoadAction::LoadAction(ApplicationManager * pApp) :Action(pApp)
{
}


LoadAction::~LoadAction()
{
}

//Execute the action
void LoadAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	if (pIn->confirmAction("Save"))
		pManager->ExecuteAction(SAVE);
	ReadActionParameters();
	if (loadfile.is_open()) {
		pManager->restartApp();
		string read;
		//Loading Draw Color
		loadfile >> read;
		if (read == "Black")
			UI.DrawColor = sf::Color(0, 0, 0);
		else if (read == "White")
			UI.DrawColor = sf::Color(255, 255, 255);
		else if (read == "Green")
			UI.DrawColor = sf::Color(0, 255, 0);
		else if (read == "Red")
			UI.DrawColor = sf::Color(255, 0, 0);
		else if (read == "Blue")
			UI.DrawColor = sf::Color(0, 0, 255);
		else if (read == "Turquoise")
			UI.DrawColor = sf::Color(0, 255, 127.5);
		else if (read == "Yellow")
			UI.DrawColor = sf::Color(255, 255, 127.5);
		else if (read == "Orange")
			UI.DrawColor = sf::Color(255, 127.5, 0);
		else
			UI.DrawColor = sf::Color(127.5, 127.5, 127.5);

		////////////////////////////////
		//Loading Fill Color
		loadfile >> read;
		if (read == "Black")
			UI.FillColor = sf::Color(0, 0, 0);
		else if (read == "White")
			UI.FillColor = sf::Color(255, 255, 255);
		else if (read == "Green")
			UI.FillColor = sf::Color(0, 255, 0);
		else if (read == "Red")
			UI.FillColor = sf::Color(255, 0, 0);
		else if (read == "Blue")
			UI.FillColor = sf::Color(0, 0, 255);
		else if (read == "Turquoise")
			UI.FillColor = sf::Color(0, 255, 127.5);
		else if (read == "Yellow")
			UI.FillColor = sf::Color(255, 255, 127.5);
		else if (read == "Orange")
			UI.FillColor = sf::Color(255, 127.5, 0);
		else if (read == "Grey")
			UI.FillColor = sf::Color(127.5, 127.5, 127.5);
		else
			UI.FillColor = sf::Color::Transparent;
		//////////////////////////////
		//Loading Background Color
		loadfile >> read;
		if (read == "Dark_Grey")
			UI.BkGrndColor = sf::Color(190, 190, 190);
		else if (read == "Beige")
			UI.BkGrndColor = sf::Color(255, 250, 205);
		else if (read == "Light_Grey")
			UI.BkGrndColor = sf::Color(220, 220, 220);
		else
			UI.BkGrndColor = sf::Color(0, 200, 200);

		int count;
		loadfile >> count;
		CFigure* currentFigure;
		for (int i = 0; i < count; i++)
		{
			loadfile >> read;
			if (read == "Line")
			{
				currentFigure = new CLine;
				currentFigure->Load(loadfile);
				pManager->AddFigure(currentFigure);
			}
			else if (read == "Circle")
			{
				currentFigure = new CCircle;
				currentFigure->Load(loadfile);
				pManager->AddFigure(currentFigure);
			}
			else if (read == "Rectangle")
			{
				currentFigure = new CRectangle;
				currentFigure->Load(loadfile);
				pManager->AddFigure(currentFigure);
			}
			else if (read == "Triangle")
			{
				currentFigure = new CTriangle;
				currentFigure->Load(loadfile);
				pManager->AddFigure(currentFigure);
			}
		}
		pOut->PrintMessage("File Loaded succefully!");
		loadfile.close();
	}
	else
		pOut->PrintMessage("Can't open File!");
}

void LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Load: Enter file name");
	string fileName = pIn->GetSrting(pOut);
	if (fileName.rfind(".txt") != 4)
		fileName += ".txt";
	pOut->SetWindowTitle(fileName);
	loadfile.open(fileName, ios::in);
}
