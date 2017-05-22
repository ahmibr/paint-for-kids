#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "DataManager.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure ** selectedList; //List of selected Figures
	DataManager* pData; //pointer to data manager to clean up
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	// -- Figures Management Functions
	void fixFigList(); //utility function to rearrange figurelist after deleting items

public:
	ApplicationManager();
	~ApplicationManager();

	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType); //Creates an action and executes it

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	void removeFigure(int ID); //Remove figure by it's ID
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure *GetFigure(int index) const;//get figure given index
	void restartApp(); //delete figures before loading new graph
	int GetFigureCount() const; //Search for a figure given a point inside the figure
	void SelectAllFigures();
	void DeSelectAllFigures();
	void Save(ofstream& savefile);   //Loop on figures to save them

	// -- selected Figures Management Functions
	CFigure ** getSelectedList(int &size);
	int getSelectedCount()const;
	bool ChangeSelectedColor(GfxInfo selectedColor);//Changes the color of selected objects if no selected figures return false
	bool ResizeFigures(float resize);
	bool RotateFigures(float rotate);
	void moveFigures(int dx, int dy);
	bool DeleteFigures();

	// -- Play mode related Functions
	CFigure * GetFigure(int x, int y, CFigure ** figures) const;//get figure from a specific figure list
	void UpdateInterface(CFigure ** figures) const;//Draw all figures for play mode on the user interface for play mode scramble and find mode	-BM
	void ShowAllFigures();
	void HideAllFigures();
	void ToLeftHalf();//scales the figures to half the screen
	void RandomizePositionsRight(CFigure ** figures);//Randomize the positions of figures to the right half of the screen
	void RestoreFromHalf();//scales the figures to full the screen
	void deleteFigureArray(CFigure ** figures);//delete figure array
	CFigure ** createCopyOfFigures();//Create a copy of the figure array and return it
	CFigure * getRandomFigure();//returns a random visible figure and select it
	int NumberOfFigureOfType(CFigure * refrenceFigure);//returns number of figures with same type as reference figure
	int NumberOfFigureOfColor(CFigure * refrenceFigure);//returns number of figures with same color as reference figure
	int NumberOfFigureOfColorAndType(CFigure * refrenceFigure);//returns largest area in figures
	float LargestArea();//returns number of figures with same type and color as reference figure

	//Search for a figure given index of figure

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
};

#endif