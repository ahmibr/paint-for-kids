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
	pOut->PrintMessage("Load: Do you want to save your current work? Y or N");
	string choice = pIn->GetSrting(pOut);
	if (choice == "Y" || choice == "y")
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

		int count, ID;
		GfxInfo gfx;
		loadfile >> count;
		CFigure* currentFigure;
		for (int i = 0; i < count; i++)
		{
			loadfile >> read;
			loadfile >> ID;
			if (read == "Line")
			{
				Point p1, p2;
				loadfile >> p1.x;
				loadfile >> p1.y;
				loadfile >> p2.x;
				loadfile >> p2.y;
				loadfile >> gfx.BorderWdth;
				readColors(gfx, true);
				currentFigure = new CLine(p1, p2, gfx);
				currentFigure->setID(ID);
				pManager->AddFigure(currentFigure);
			}
			else if (read == "Circle")
			{
				Point p1, p2;
				float r;
				loadfile >> p1.x;
				loadfile >> p1.y;
				loadfile >> r;
				loadfile >> gfx.BorderWdth;
				readColors(gfx, false);
				currentFigure = new CCircle(p1,r, gfx);
				currentFigure->setID(ID);
				pManager->AddFigure(currentFigure);
			}
			else if (read == "Rectangle")
			{
				Point p1, p2;
				loadfile >> p1.x;
				loadfile >> p1.y;
				loadfile >> p2.x;
				loadfile >> p2.y;
				loadfile >> gfx.BorderWdth;
				readColors(gfx, false);
				currentFigure = new CRectangle(p1, p2, gfx);
				currentFigure->setID(ID);
				pManager->AddFigure(currentFigure);
			}
			else if (read == "Triangle")
			{
				Point p1, p2, p3;
				loadfile >> p1.x;
				loadfile >> p1.y;
				loadfile >> p2.x;
				loadfile >> p2.y;
				loadfile >> p3.x;
				loadfile >> p3.y;
				loadfile >> gfx.BorderWdth;
				readColors(gfx, false);
				currentFigure = new CTriangle(p1, p2, p3, gfx);
				currentFigure->setID(ID);
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
	loadfile.open(fileName, ios::in);
}

void LoadAction::readColors(GfxInfo & GFX,bool isLine)
{
	string color;
	loadfile >> color;
	if (color == "Black")
		GFX.DrawClr = sf::Color(0, 0, 0);
	else if (color == "White")
		GFX.DrawClr = sf::Color(255, 255, 255);
	else if (color == "Green")
		GFX.DrawClr = sf::Color(0, 255, 0);
	else if (color == "Red")
		GFX.DrawClr = sf::Color(255, 0, 0);
	else if (color == "Blue")
		GFX.DrawClr = sf::Color(0, 0, 255);
	else if (color == "Turquoise")
		GFX.DrawClr = sf::Color(0, 255, 127.5);
	else if (color == "Yellow")
		GFX.DrawClr = sf::Color(255, 255, 127.5);
	else if (color == "Orange")
		GFX.DrawClr = sf::Color(255, 127.5, 0);
	else
		GFX.DrawClr = sf::Color(127.5, 127.5, 127.5);
	if (isLine)
		return;
	loadfile >> color;
	if (color == "Black")
		GFX.FillClr = sf::Color(0, 0, 0);
	else if (color == "White")
		GFX.FillClr = sf::Color(255, 255, 255);
	else if (color == "Green")
		GFX.FillClr = sf::Color(0, 255, 0);
	else if (color == "Red")
		GFX.FillClr = sf::Color(255, 0, 0);
	else if (color == "Blue")
		GFX.FillClr = sf::Color(0, 0, 255);
	else if (color == "Turquoise")
		GFX.FillClr = sf::Color(0, 255, 127.5);
	else if (color == "Yellow")
		GFX.FillClr = sf::Color(255, 255, 127.5);
	else if (color == "Orange")
		GFX.FillClr = sf::Color(255, 127.5, 0);
	else if (color == "Grey")
		GFX.FillClr = sf::Color(127.5, 127.5, 127.5);
	else
		GFX.isFilled = false;

}