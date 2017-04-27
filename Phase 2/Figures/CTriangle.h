#ifndef CTRING_H
#define CTRING_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point p1; 
	Point p2;
	Point p3;
	float lengthP1P2; //length from p1 to p2
	float lengthP1P3; //length from p1 to p3
	float lengthP2P3; //length from p2 to p3
	virtual bool clickedInside(int x, int y) const;//utility function to check if clicked inside figure
	virtual bool clickedOnBorder(int x, int y) const;//utility function to check if clicked on border of figure
	float area(Point, Point, Point) const; //utility function to calculate area
	void updateInfo();//utility function to recalculate lengthes after assigning points
public:
	CTriangle(Point , Point,Point,GfxInfo FigureGfxInfo);
	CTriangle(const CTriangle&); //copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int dy);//move shape by dx and dy
	virtual Point getPoint() const;		//get point to do some calculations
	virtual float getArea() const;
	virtual string getType() const;
	void setPoints(Point, Point, Point);//function to manage assigning points
	virtual bool isClicked(int x, int y) const;
	virtual string printInfo() const;
	virtual void Save(ofstream &OutFile); //Save Triangle parameters to the file
};

#endif