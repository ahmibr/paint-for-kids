#include "SaveAction.h"

#include "..\ApplicationManager.h"




SaveAction::SaveAction(ApplicationManager * pApp) :Action(pApp)
{
}


SaveAction::~SaveAction()
{
}

//Execute the action
void SaveAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if (savefile.is_open()) {

		//Saving Draw Color
		if (operator==(UI.DrawColor, sf::Color(0, 0, 0)))
			savefile << "Black  ";
		else if (operator==(UI.DrawColor, sf::Color(255, 255, 255)))
			savefile << "White  ";
		else if (operator==(UI.DrawColor, sf::Color(0, 255, 0)))
			savefile << "Green  ";
		else if (operator==(UI.DrawColor, sf::Color(255, 0, 0)))
			savefile << "Red  ";
		else if (operator==(UI.DrawColor, sf::Color(0, 0, 255)))
			savefile << "Blue  ";
		else if (operator==(UI.DrawColor, sf::Color(0, 255, 127.5)))
			savefile << "Turquoise  ";
		else if (operator==(UI.DrawColor, sf::Color(255, 255, 127.5)))
			savefile << "Yellow  ";
		else if (operator==(UI.DrawColor, sf::Color(255, 127.5, 0)))
			savefile << "Orange  ";
		else
			savefile << "Grey  ";
		////////////////////////////////
		//Saving Fill Color
		if (operator==(UI.FillColor, sf::Color(0, 0, 0)))
			savefile << "Black  ";
		else if (operator==(UI.FillColor, sf::Color(255, 255, 255)))
			savefile << "White  ";
		else if (operator==(UI.FillColor, sf::Color(0, 255, 0)))
			savefile << "Green  ";
		else if (operator==(UI.FillColor, sf::Color(255, 0, 0)))
			savefile << "Red  ";
		else if (operator==(UI.FillColor, sf::Color(0, 0, 255)))
			savefile << "Blue  ";
		else if (operator==(UI.FillColor, sf::Color(0, 255, 127.5)))
			savefile << "Turquoise  ";
		else if (operator==(UI.FillColor, sf::Color(255, 255, 127.5)))
			savefile << "Yellow  ";
		else if (operator==(UI.FillColor, sf::Color(255, 127.5, 0)))
			savefile << "Orange  ";
		else if (operator==(UI.FillColor, sf::Color(127.5, 127.5, 127.5)))
			savefile << "Grey  ";
		else
			savefile << "NO_Fill  ";
		//////////////////////////////
		//Saving Background Color
		if (operator==(UI.BkGrndColor, sf::Color(190, 190, 190)))
			savefile << "Dark_Grey  ";
		else if (operator==(UI.BkGrndColor, sf::Color(255, 250, 205)))
			savefile << "Beige  ";
		else if (operator==(UI.BkGrndColor, sf::Color(220, 220, 220)))
			savefile << "Light_Grey ";
		else
			savefile << "Turquoise  ";
		savefile << endl;
		int count = pManager->GetFigureCount();
		savefile << count;
		savefile << endl;
		CFigure* currentFigure;
		for (int i = 0; i < count; i++)
		{
			currentFigure = pManager->GetFigure(i);
			currentFigure->Save(savefile);
			savefile << endl;
		}
		pOut->PrintMessage("File saved succefully!");
		savefile.close();
	}
	else
		pOut->PrintMessage("Can't open File!");
}

void SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter file name");
	string fileName = pIn->GetSrting(pOut);
	if (fileName.rfind(".txt") != 4)
		fileName += ".txt";
	pOut->SetWindowTitle(fileName);
	savefile.open(fileName, ios::out);
}