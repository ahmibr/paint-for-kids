#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\DEFS.h"
#include "..\GUI\Output.h"
#include<fstream>
//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	static int count;
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	virtual bool clickedInside(int x, int y) const = 0;
	virtual bool clickedOnBorder(int x, int y) const = 0;
public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);
	virtual CFigure* copyClone() = 0; //a clone to apply polymorphism on copy construtors
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual bool isClicked(int x, int y) const = 0; //function to check if given point is related to the figure
	virtual void Draw(Output* pOut) const = 0;		//Draw the figure
	int getID(); //get ID
	void setID(int); //force set ID (Caution: Do it only in Load, otherwise it'll break uniqness of ID)
	void ChngDrawClr(sf::Color Dclr);	//changes the figure's drawing color
	void ChngFillClr(sf::Color Fclr);	//changes the figure's filling color
	void ChngBrdrWidth(int width);		//changes the figure's border width
	string getDrawClrName() const; //a function to return Draw color as a word (e.g green, yellow ... etc )
	string getFillClrName() const; //a function to return Fill color as a word (e.g green, yellow ... etc )
	virtual float getArea() const = 0;
	virtual string getType() const = 0;
	virtual Point getPoint() const = 0;		//get point to do some calculations
	virtual string printInfo() const = 0; //print info about selected item
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	virtual void Move(int dx,int dy) = 0;		//Move the figure
	
	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif