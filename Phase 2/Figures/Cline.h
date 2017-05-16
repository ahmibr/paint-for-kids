#ifndef CLINE_H
#define CLINE_H

#include "CFigure.h"

class CLine : public CFigure
{
private:
	Point p1;//left point
	Point p2;//right point
	float length;//length of the line
	virtual bool clickedInside(int x, int y) const;//utility function to check if clicked inside figure
	virtual bool clickedOnBorder(int x, int y) const;//utility function to check if clicked on border of figure
	void updateInfo();//utility function to recalculate length after assigning points
	Point tempP1, tempP2;
public:
	CLine();
	CLine(Point, Point, GfxInfo FigureGfxInfo);
	CLine(const CLine&); //copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int dy);
	virtual void Rotate(float rotate);
	virtual void Resize(float size);
	//move shape by dx and dy
	virtual Point getPoint() const;		//get point to do some calculations
	virtual float getArea() const;
	virtual string getType() const;
	virtual string getFillClrName() const; //overrided from base, as line doesn't have fill color
	virtual bool isOutOfBorder(int = 0, int = 0) const;
	void setPoints(Point, Point);//function to manage assigning points
	virtual bool isClicked(int x, int y) const;//function to check if given point is related to the figure
	virtual string printInfo() const;
	virtual void Save(ofstream &OutFile); //Save Line parameters to the file
	int getOriginXpos();
	int getOriginYpos();
	int getHeight();
	int getWidth();
	void setCurrCordTemp();
	void setTempCord();
};

#endif